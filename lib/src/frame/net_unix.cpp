
#include <unistd.h>

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
, m_listen_thread(NULL)
, m_epoll_fd(epoll_create(10240))
{

}

NetManager::~NetManager()
{
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

	if (m_listen_thread)
	{
		delete m_listen_thread;
	}
}

unsigned int NetManager::AddMsgHandler(MsgCallBack *call_back)
{
	MsgHandler *mh = new MsgHandler;
	mh->msg[BaseMsg::MSG_ACCEPT] = new AcceptMsg(call_back);
	mh->msg[BaseMsg::MSG_RECV] = new RecvMsg(call_back);
	mh->msg[BaseMsg::MSG_DISCONNECT] = new DisconnectMsg(call_back);
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

void *Loop(void *arg)
{
	NetManager *manager = (NetManager *)arg;
	manager->Loop();
	return NULL;
}


void NetManager::Loop()
{
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
			// Ð´log
			usleep(10000);
		}
	}
}


void NetManager::InitNetHandler(NetHandler *handler)
{
	// ÉèÖÃ³É·Ç×èÈû
	unsigned long b = 1;
	NetCommon::Ioctl(handler->m_sock, FIONBIO, &b);

	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.ptr = (void *)handler;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handler->m_sock, &ev) == -1)
	{
		// Ìí¼ÓÊ§°Ü
	}
}

NetHandle NetManager::AddNetHandler(NetHandler *handler)
{
	InitNetHandler(handler);
	handler->m_handle = m_net_handler.Insert(handler);
	return handler->m_handle;
}


void NetManager::RemoveHandler(NetHandle handle, int reason)
{
	RemoveInfo info{ handle, reason };
	m_invalid_handle.Push(info);
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
		struct epoll_event ev;
		ev.events = EPOLLIN | EPOLLET;
		ev.data.ptr = (void *)(*itr);
		if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, (*itr)->m_sock, &ev) == -1)
		{
			// Ìí¼ÓÊ§°Ü
		}
	}
	m_replace_handler.Clear();
}

void NetManager::ClearHandler()
{
	struct epoll_event ev;
	for (INVALID_HANDLE::iterator itr = m_invalid_handle.Begin(); itr != m_invalid_handle.End(); ++itr)
	{

		NetHandler *handler = 0;
		if (m_net_handler.Erase(itr->handle, handler))
		{

			epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handler->m_sock, &ev);
			NetCommon::Close(handler->m_sock);
			PushMsg(handler, BaseMsg::MSG_DISCONNECT, (const char *)&itr->reason, sizeof(itr->reason));
			delete handler;
		}
	}
	m_invalid_handle.Clear();
}

bool NetManager::Send(NetHandle handle, const char *buf, unsigned int length)
{
	MutexLock lock(&m_net_mutex);
	NET_HANDLER_ARRAY::iterator itr = m_net_handler.Find(handle);
	if (itr == m_net_handler.End())
	{
		return false;
	}

	if ((*itr)->Type() == NetHandler::LISTENER)
	{
		Listener *listener = (Listener *)(*itr);
		if (listener != NULL)
		{
			listener->Send(buf, length);
			listener->RegisterWriteFD();
			return true;
		}
	}
	return false;
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
					// ÄÚ´æ½»¸øÏÂÓÎ´¦Àí
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


void NetManager::Listen()
{
	m_listen_thread = new std::thread(::Loop, this);
}

void NetManager::Exit()
{
	m_is_run = false;
}

void NetManager::Wait()
{
	if (m_listen_thread != NULL)
	{
		m_listen_thread->join();
	}
}


