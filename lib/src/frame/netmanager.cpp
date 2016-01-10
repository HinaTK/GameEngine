
#ifdef __unix
#include <unistd.h>
#endif

#include "frame/netmanager.h"
#include "common/protocol/messageheader.h"
#include "netcommon.h"
#include "accepter.h"
#include "webaccepter.h"
#include "baselistener.h"
#include "weblistener.h"
#include "handshaker.h"


NetManager::NetManager()
: m_is_run(true)
#ifdef WIN32
, m_max_fd(0)
#endif
#ifdef __unix
, m_epoll_fd(epoll_create(10240))
#endif
{
	
}

NetManager::~NetManager()
{
#ifdef WIN32
    FD_ZERO(&m_read_set);
    FD_ZERO(&m_write_set);
#endif

    for (MSG_HANDLER::iterator itr = m_msg_handler.Begin(); itr != m_msg_handler.End(); ++itr)
    {
        delete (*itr)->msg[BaseMsg::MSG_ACCEPT];
        delete (*itr)->msg[BaseMsg::MSG_RECV];
        delete (*itr)->msg[BaseMsg::MSG_DISCONNECT];
        delete (*itr);
    }

    for (NET_HANDLER_ARRAY::iterator itr = m_net_handler.Begin(); itr != m_net_handler.End(); ++itr)
    {
        NetCommon::Close((*itr)->m_sock);
        delete (*itr);
    }
}

unsigned int NetManager::AddMsgHandler(MsgCallBack *call_back)
{
	MsgHandler *mh = new MsgHandler;
	mh->msg[BaseMsg::MSG_ACCEPT]		= new AcceptMsg(call_back);
	mh->msg[BaseMsg::MSG_RECV]			= new RecvMsg(call_back);
	mh->msg[BaseMsg::MSG_DISCONNECT]	= new DisconnectMsg(call_back);
	return m_msg_handler.Insert(mh);
}

bool NetManager::InitServer(char *ip, unsigned short port, int backlog, Accepter *accepter, MsgCallBack *call_back)
{
	printf("Init Server ip = %s, port = %d\n", ip, port);
	SOCKET net_id = 0;
	NetCommon::StartUp();
	if (!NetCommon::Init(ip, port, backlog, net_id))
	{
        delete accepter;
		return false;
	}
#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
    ev.data.ptr = (void *)accepter;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, net_id, &ev) < 0)
	{
        delete accepter;
		return false;	// 写log
	}
#endif

	accepter->m_msg_index = AddMsgHandler(call_back);
	accepter->m_sock = net_id;
	AddNetHandler(accepter);
	printf("Init Server Success\n");
	return true;
}

/*
	
*/
NetHandle NetManager::ConnectServer(const char *ip, unsigned short port, Listener *listener, MsgCallBack *call_back)
{
	printf("connect to Server ip = %s, port = %d\n", ip, port);

	NetCommon::StartUp();

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		printf("Create socket error\n");
		NetCommon::CleanUp();
		return INVALID_NET_HANDLE;
	}

	if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		printf("Connect server error %d\n", NetCommon::Error());
		NetCommon::Close(sock);
		NetCommon::CleanUp();
		return INVALID_NET_HANDLE;
	}

#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
    ev.data.ptr = (void *)listener;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, sock, &ev) < 0)
	{
		fprintf(stderr, "epoll set insertion error: fd=%d\n", sock);
		return INVALID_NET_HANDLE;
	}
#endif

	printf("Connect Server Success\n");
	listener->m_msg_index = AddMsgHandler(call_back);
	listener->m_sock = sock;
	return AddNetHandler(listener);
}

void NetManager::Listen()
{
#ifdef WIN32
	int ret = 0;
	SOCKET	max_fd = 0;
	fd_set	temp_read_set;
	fd_set	temp_write_set;
	FD_ZERO(&temp_read_set);
	FD_ZERO(&temp_write_set);
	struct timeval tv;	//超时参数
	tv.tv_sec = 0;		//秒
	tv.tv_usec = 10000;	//微秒,10毫秒
	while (m_is_run)
	{
		max_fd = GetSocketInfo(temp_read_set, temp_write_set);
		ret = select(max_fd + 1, &temp_read_set, &temp_write_set, NULL, &tv);
		if (ret > 0)
		{
			NetManager::NET_HANDLER_ARRAY::iterator itr = m_net_handler.Begin();
			for (; itr != m_net_handler.End(); ++itr)
			{
				if (FD_ISSET((*itr)->m_sock, &temp_read_set))
				{
					(*itr)->OnCanRead();
				}
				if (FD_ISSET((*itr)->m_sock, &temp_write_set))
				{
					(*itr)->OnCanWrite();
				}
			}
			ReplaceHandler();
			ClearHandler();
		}
		else if (max_fd <= 0)
		{
			Sleep(10);
		}
	}
#endif

#ifdef __unix
	static struct epoll_event events[MAX_EPOLL_SIZE];
	int fd_num = 0;
	while (m_is_run)
	{
		fd_num = epoll_wait(m_epoll_fd, events, MAX_EPOLL_SIZE, 10);
		if (fd_num > 0)
		{
			for (int i = 0; i < fd_num; ++i)
			{
				if (events[i].events & EPOLLIN)
				{
					((NetHandler*)events[i].data.ptr)->OnCanRead();
				}
				if (events[i].events & EPOLLOUT)
				{
					((NetHandler*)events[i].data.ptr)->OnCanWrite();
				}
			}
			ReplaceHandler();
			ClearHandler();
		}
		else
		{
			// 写log
            usleep(10000);
		}
	}
#endif
}


void NetManager::InitNetHandler(NetHandler *handler)
{
	// 设置成非阻塞
    unsigned long b = 1;
	NetCommon::Ioctl(handler->m_sock, FIONBIO, &b);
#ifdef WIN32
	FD_SET(handler->m_sock, &m_read_set);
	handler->m_sock > m_max_fd ? m_max_fd = handler->m_sock : 0;
	// 做一个网络id排序，方便删除时找到最大id
#endif

#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.ptr = (void *)handler;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handler->m_sock, &ev) == -1)
	{
		// 添加失败
	}
#endif
}

NetHandle NetManager::PushNetHandler(NetHandler *handler)
{
	handler->m_handle = m_net_handler.Insert(handler);
	return handler->m_handle;
}

NetHandle NetManager::AddNetHandler(NetHandler *handler)
{
	InitNetHandler(handler);
	return PushNetHandler(handler);
}

void NetManager::RemoveHandler(NetHandle handle)
{
	m_invalid_handle.Push(handle);
}

void NetManager::AddReplaceHandler(NetHandler *handler)
{
	m_net_handler.Erase(handler->m_handle);
	handler->m_handle = m_net_handler.Insert(handler);
	m_replace_handler.Push(handler);
}

void NetManager::ReplaceHandler()
{
	if (m_replace_handler.Size() <= 0)
	{
		return;
	}
	for (REPLACE_HANDLER::iterator itr = m_replace_handler.Begin(); itr != m_replace_handler.End(); ++itr)
	{
#ifdef WIN32
		FD_CLR((*itr)->m_sock, &m_write_set);
#endif
#ifdef __unix
		struct epoll_event ev;
		ev.events = EPOLLIN | EPOLLET;
		ev.data.ptr = (void *)(*itr);
		if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, (*itr)->m_sock, &ev) == -1)
		{
			// 添加失败
		}
#endif
	}
	m_replace_handler.Clear();
}

void NetManager::ClearHandler()
{
#ifdef __unix
	struct epoll_event ev;
#endif
	for (INVALID_HANDLE::iterator itr = m_invalid_handle.Begin(); itr != m_invalid_handle.End(); ++itr)
	{

		NetHandler *handler = 0;
		if (m_net_handler.Erase(*itr, handler))
		{
#ifdef WIN32
			FD_CLR(handler->m_sock, &m_read_set);
			FD_CLR(handler->m_sock, &m_write_set);
#endif
#ifdef __unix
			epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handler->m_sock, &ev);
#endif
			NetCommon::Close(handler->m_sock);
			PushMsg(handler, BaseMsg::MSG_DISCONNECT, NULL, 0);
			delete handler;
		}	
	}
	m_invalid_handle.Clear();
}

#ifdef WIN32
SOCKET NetManager::GetSocketInfo(fd_set &read_set, fd_set &write_set)
{
	read_set = m_read_set;
	write_set = m_write_set;
	return m_max_fd;
}
#endif	

void NetManager::Send(NetHandle handle, const char *buf, unsigned int length)
{
	NET_HANDLER_ARRAY::iterator itr = m_net_handler.Find(handle);
	if (itr == m_net_handler.End())
	{
		return;
	}

	if ((*itr)->Type() == NetHandler::LISTENER)
	{
		Listener *listener = (Listener *)(*itr);
		if (listener != NULL)
		{
            listener->Send(buf, length);
            listener->RegisterWriteFD();
		}
	}
}

void NetManager::PushMsg(NetHandler *handler, unsigned short msg_type, const char *data, unsigned int len)
{
	GameMsg *game_msg = new GameMsg(handler->m_msg_index, msg_type, handler->m_handle, data, len);
	m_queue.Push(game_msg);
}

void NetManager::Update()
{
	static GameMsg *msg;
	do
	{
		if (m_queue.Pop(msg))
		{
			if (msg != NULL)
			{
				if (msg->handle >= 0)
				{
					m_msg_handler[msg->msg_index]->msg[msg->msg_type]->Recv(msg);
					// 内存交给下游处理
					// delete (*msg);
				}
				else
				{
					delete msg;
				}
			}
		}
		else
		{
			break;
		}
	} while (true);
}


