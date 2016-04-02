
#include "net_win.h"
#include "netcommon.h"

NetManager::NetManager()
: NetBase()
, m_max_fd(0)
{
	FD_ZERO(&m_read_set);
	FD_ZERO(&m_write_set);
}

NetManager::~NetManager()
{
	
}

void NetManager::Loop()
{
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
			m_net_mutex.lock();
			NET_HANDLER_ARRAY::iterator itr = m_net_handler.Begin();
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
			m_net_mutex.unlock();
		}
		else if (max_fd <= 0)
		{
			Sleep(10);
		}
	}
}

void NetManager::InitNetHandler(NetHandler *handler)
{
	// 设置成非阻塞
	unsigned long b = 1;
	NetCommon::Ioctl(handler->m_sock, FIONBIO, &b);
	FD_SET(handler->m_sock, &m_read_set);
	handler->m_sock > m_max_fd ? m_max_fd = handler->m_sock : 0;
	// 做一个网络id排序，方便删除时找到最大id
}

void NetManager::ReplaceHandler()
{
	if (m_replace_handler.Size() <= 0)
	{
		return;
	}
	for (REPLACE_HANDLER::iterator itr = m_replace_handler.Begin(); itr != m_replace_handler.End(); ++itr)
	{
		FD_CLR((*itr)->m_sock, &m_write_set);
	}
	m_replace_handler.Clear();
}

void NetManager::ClearHandler()
{
	for (INVALID_HANDLE::iterator itr = m_invalid_handle.Begin(); itr != m_invalid_handle.End(); ++itr)
	{
		NetHandler *handler = NULL;
		if (m_net_handler.Erase(itr->handle, handler))
		{
			FD_CLR(handler->m_sock, &m_read_set);
			FD_CLR(handler->m_sock, &m_write_set);

			NetCommon::Close(handler->m_sock);
			PushMsg(handler, BaseMsg::MSG_DISCONNECT, (const char *)&itr->reason, sizeof(itr->reason));
			delete handler;
		}
	}
	m_invalid_handle.Clear();
}

void NetManager::SetCanWrite(NetHandler *handler)
{
	FD_SET(handler->m_sock, &m_write_set);
}

void NetManager::SetCanNotWrite(NetHandler *handler)
{
	FD_CLR(handler->m_sock, &m_write_set);
}

SOCKET NetManager::GetSocketInfo(fd_set &read_set, fd_set &write_set)
{
	read_set = m_read_set;
	write_set = m_write_set;
	return m_max_fd;
}