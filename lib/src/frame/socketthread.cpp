
#include "socketthread.h"
#include "netcommon.h"
#include "netmanager.h"


SocketThread::SocketThread(ThreadManager *manager)
: BaseThread(manager)
, m_net_manager(NULL)
, m_max_fd(0)
{
	FD_ZERO(&m_read_set);
	FD_ZERO(&m_write_set);
	FD_ZERO(&m_tmp_read_set);
	FD_ZERO(&m_tmp_write_set);
	m_tv.tv_sec = 0;		//Ãë
	m_tv.tv_usec = 10000;	//Î¢Ãë,10ºÁÃë
}


void SocketThread::Init(void *arg)
{
	m_net_manager = (NetManager *)arg;
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

void SocketThread::RecvMsg(short type, unsigned char sid, int len, const char *data)
{
	switch (type)
	{
	case NetBase::STM_ADD_HANDLER:
		//m_net_manager->AddNetHandler()
	default:
		break;
	}
}

