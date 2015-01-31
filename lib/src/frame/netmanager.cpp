
#include "frame/netmanager.h"
#include "common/protocol/messageheader.h"
#include "common/socketdef.h"
#include "netcommon.h"
#include "accepter.h"
#include "webaccepter.h"
#include "baselistener.h"
#include "weblistener.h"
#include "handshaker.h"

NetManager::~NetManager()
{
#ifdef WIN32
	FD_ZERO(&m_read_set);
	FD_ZERO(&m_write_set);
#endif
}

#ifdef WIN32
NetManager::NetManager()
: m_max_fd(0)
{

}
#endif // WIN32
#ifdef __unix
NetManager::NetManager()
{

}
#endif

bool NetManager::InitServer(char *ip, unsigned short port, int backlog, NetID &net_id, bool is_web)
{
	NetCommon::StartUp();
	if (!NetCommon::Init(ip, port, backlog, net_id))
	{
		return false;
	}
#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = net_id;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, net_id, &ev) < 0)
	{
		return false;	// Ð´log
	}
#endif

//	unsigned long _ip = inet_addr(ip);
// 	if (ip_n == INADDR_NONE) return false;
// 
// 	IP ip_host = ntohl(ip_n);
	NetHandler *handler;
	if (is_web)
	{
		handler = new WebAccepter(this, NetHandler::WEB_ACCEPTER);
	}
	else
	{
		unsigned long _ip = inet_addr(ip);
		handler = new Accepter(this, NetHandler::ACCEPTER, _ip);
	}
	handler->m_net_id = net_id;
	AddNetHandler(handler);
	return true;
}

bool NetManager::ConnectServer(char *ip, unsigned short port, NetID &net_id)
{
	printf("connect to Server ip = %s, port = %d\n", ip, port);
#ifdef WIN32
	WSADATA data;
	SOCKADDR_IN serverAddr;

	WSAStartup(MAKEWORD(1, 1), &data);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);


	net_id = socket(AF_INET, SOCK_STREAM, 0);
	if (net_id == INVALID_SOCKET)
	{
		printf("init connect server error\n");
		WSACleanup();
		return false;
	}

	int ret = connect(net_id, (LPSOCKADDR)&serverAddr, sizeof(serverAddr));
	if (ret == SOCKET_ERROR)
	{
		printf("can not connect server\n");
		closesocket(net_id);
		WSACleanup();
		return false;
	}
#endif
#ifdef __unix
	struct epoll_event ev;
	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);

	net_id = socket(AF_INET, SOCK_STREAM, 0);
	if (net_id == -1)
	{
		printf("init connect server error\n");
		return false;
	}

	if (connect(net_id, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		printf("can not connect server\n");
		NetCommon::Close(net_id);
		return false;
	}
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = net_id;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, net_id, &ev) < 0)
	{
		fprintf(stderr, "epoll set insertion error: fd=%d\n", net_id);
		return false;
	}
#endif
	BaseListener *handler = new BaseListener(this, NetHandler::LISTENER);
	handler->m_net_id = net_id;
	AddNetHandler(handler);

	printf("Connect Server success\n");
	return true;
}

void NetManager::Listen()
{
#ifdef WIN32
	int ret = 0;
	NetID	max_fd = 0;
	fd_set	temp_read_set;
	fd_set	temp_write_set;
	FD_ZERO(&temp_read_set);
	FD_ZERO(&temp_write_set);
	while (1)
	{
		max_fd = GetSocketInfo(temp_read_set, temp_write_set);
		ret = select(max_fd + 1, &temp_read_set, &temp_write_set, NULL, NULL);
		if (ret > 0)
		{
			NetManager::NET_HANDLER_ARRAY::iterator itr = m_net_handler.Begin();
			for (; itr != m_net_handler.End(); ++itr)
			{
				if (FD_ISSET((*itr)->m_net_id, &temp_read_set))
				{
					(*itr)->OnCanRead();
				}
				if (FD_ISSET((*itr)->m_net_id, &temp_write_set))
				{
					(*itr)->OnCanWrite();
				}
			}

			ClearHandler();
		}
		else
		{
			// Ð´log
		}
	}
#endif

#ifdef __unix
	static struct epoll_event events[MAX_EPOLL_SIZE];
	int fd_num = 0;
	int time_out = -1;

	while (true)
	{
		fd_num = epoll_wait(m_epoll_fd, events, MAX_EPOLL_SIZE, time_out);
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
			ClearHandler();
		}
		else
		{
			// Ð´log
		}
	}
#endif
}

NetHandle NetManager::AddNetHandler(NetHandler *handler)
{
	handler->m_handle = m_net_handler.Insert(handler);
	// ÉèÖÃ³É·Ç×èÈû
	unsigned long b;
	NetCommon::Ioctl(handler->m_net_id, FIONBIO, &b);
#ifdef WIN32
	FD_SET(handler->m_net_id, &m_read_set);
	handler->m_net_id > m_max_fd ? m_max_fd = handler->m_net_id : 0;
	// ×öÒ»¸öÍøÂçidÅÅÐò£¬·½±ãÉ¾³ýÊ±ÕÒµ½×î´óid
#endif

#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.ptr = (void *)handler;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handler->m_net_id, &ev) == -1)
	{
		// Ìí¼ÓÊ§°Ü
	}
#endif
	return handler->m_handle;
}

void NetManager::RemoveHandler(NetHandle handle)
{
	m_invalid_handle.Push(handle);
}

void NetManager::ReplaceHandler(NetHandler *handler )
{
	handler->m_handle = m_net_handler.Insert(handler);
#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.ptr = (void *)handler;
	if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, handler->m_net_id, &ev) == -1)
	{
		// Ìí¼ÓÊ§°Ü
	}
#endif
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
			if (handler->Type() == NetHandler::HANDSHAKER)
			{
				HandShaker *shaker = (HandShaker *)handler;
				if (shaker != 0)
				{
					if (!shaker->IsClear())
					{
						delete handler;
						continue;
					}
				}
			}
#ifdef WIN32
			FD_CLR(handler->m_net_id, &m_read_set);
			NetCommon::Close(handler->m_net_id);
#endif
#ifdef __unix
			epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handler->m_net_id, &ev);
#endif
			delete handler;
		}	
	}
	m_invalid_handle.Clear();


}

#ifdef WIN32
NetID NetManager::GetSocketInfo(fd_set &read_set, fd_set &write_set)
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
			if (!listener->IsRegisterWrite())
			{
				listener->RegisterWriteFD();
			}
			listener->Send(buf, length);
		}
	}
}




