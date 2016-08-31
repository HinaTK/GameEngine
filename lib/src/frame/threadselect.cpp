
#include "threadselect.h"
#include "nethandler.h"
#include "lib/include/base/netcommon.h"

SocketThread::SocketThread(ThreadManager *manager)
: ThreadNet(manager)
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
		return true;
	}
	return DoSomething();
	
}

// todo 由于现在操作都是在同一线程，因此不需要异步删除断开网络？
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
			Recv(handler->m_msg_index, BaseMsg::MSG_DISCONNECT, NetMsg(handler->m_handle, (char *)&itr->show, sizeof(itr->show)));
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

bool SocketThread::CMD(short type, ThreadID sid, int len, const char *data)
{
	printf("socket thread:\n");
	if (m_net_handler.Exist(0))
	{
		printf("socket id:%d read count:%d write count:%d\n", m_net_handler[0]->m_sock, m_read_set.fd_count, m_write_set.fd_count);
		if (m_read_set.fd_count > 0) printf("server read: %d\n", m_read_set.fd_array[0]);
		if (m_write_set.fd_count > 0) printf("server write: %d\n", m_write_set.fd_array[0]);
	}
	return false;
}





