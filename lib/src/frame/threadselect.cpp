
#include "threadselect.h"
#include "netcommon.h"
#include "netmanager.h"


SocketThread::SocketThread(ThreadManager *manager, void *arg)
: ThreadNet(manager, arg)
, m_net_manager(NULL)
, m_max_fd(0)
{
	FD_ZERO(&m_read_set);
	FD_ZERO(&m_write_set);
	FD_ZERO(&m_tmp_read_set);
	FD_ZERO(&m_tmp_write_set);
	m_tv.tv_sec = 0;		//秒
	m_tv.tv_usec = 10000;	//微秒,10毫秒
}

SocketThread::~SocketThread()
{
	
	for (NET_HANDLER_ARRAY::iterator itr = m_net_handler.Begin(); itr != m_net_handler.End(); ++itr)
	{
		NetCommon::Close((*itr)->m_sock);
		delete (*itr);
	}
}

bool SocketThread::Run()
{
	m_tmp_read_set = m_read_set;
	m_tmp_write_set = m_write_set;
	int ret = select(m_max_fd + 1, &m_tmp_read_set, &m_tmp_write_set, NULL, &m_tv);
	if (ret > 0)
	{
		NET_HANDLER_ARRAY::iterator itr = m_net_handler.Begin();
		for (; itr != m_net_handler.End(); ++itr)
		{
			if (FD_ISSET((*itr)->m_sock, &m_tmp_read_set))
			{
				(*itr)->OnCanRead();
			}
			if (FD_ISSET((*itr)->m_sock, &m_tmp_write_set))
			{
				(*itr)->OnCanWrite();
			}
		}
		//ReplaceHandler();
		ClearHandler();
	}
	return true;
}

void SocketThread::ClearHandler()
{
	for (INVALID_HANDLE::iterator itr = m_invalid_handle.Begin(); itr != m_invalid_handle.End(); ++itr)
	{
		NetHandler *handler = NULL;
		if (m_net_handler.Erase(itr->handle, handler))
		{
			FD_CLR(handler->m_sock, &m_read_set);
			FD_CLR(handler->m_sock, &m_write_set);

			NetCommon::Close(handler->m_sock);
			m_net_manager->PushMsg(handler, BaseMsg::MSG_DISCONNECT, (const char *)&itr->reason, sizeof(itr->reason));
			delete handler;
		}
	}
	m_invalid_handle.Clear();
}

void SocketThread::InitNetHandler(NetHandler *handler)
{
	// 设置成非阻塞
	unsigned long b = 1;
	NetCommon::Ioctl(handler->m_sock, FIONBIO, &b);
	FD_SET(handler->m_sock, &m_read_set);
	handler->m_sock > m_max_fd ? m_max_fd = handler->m_sock : 0;
	// 做一个网络id排序，方便删除时找到最大id
}

void SocketThread::SetCanWrite(NetHandler *handler)
{
	FD_SET(handler->m_sock, &m_write_set);
}

void SocketThread::SetCanNotWrite(NetHandler *handler)
{
	FD_CLR(handler->m_sock, &m_write_set);
}





