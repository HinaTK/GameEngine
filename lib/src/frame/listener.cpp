
#include "listener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"

void Listener::OnCanRead()
{
	if (!RecvBuf() || !AnalyzeBuf())
	{
		m_net_manager->RemoveHandler(m_handle);
	}

	if (m_recv_buf.FreeLength() <= 0)
	{
		m_recv_buf.Resize(16);
	}
}

bool Listener::RecvBuf()
{
	do
	{
		int ret = recv(m_sock, m_recv_buf.GetFreeBuf(), m_recv_buf.FreeLength(), 0);
		if (ret <= 0)
		{
			if (ret == SOCKET_ERROR && NetCommon::Error() == WOULDBLOCK)
			{
				break;
			}
			return false;
		}
		m_recv_buf.AddLength(ret);
		unsigned long arg = 0;
		NetCommon::Ioctl(m_sock, FIONREAD, &arg);
		if (arg == 0)
		{
			break;
		}
		if (arg > m_recv_buf.FreeLength())
		{
			m_recv_buf.Resize(arg - m_recv_buf.FreeLength());
		}

	} while (true);

	
	return true;
}

void Listener::OnCanWrite()
{
	while (true)
	{
		if (m_send_buf_read->Length() <= 0)
		{
			{
				MutexLock ml(&m_send_mutex);
				SendBuffer *temp_buf = m_send_buf_read;
				m_send_buf_read = m_send_buf_write;
				m_send_buf_write = temp_buf;
			}

			if (m_send_buf_read->Length() <= 0)
			{
				return;
			}
		}
		while (m_send_buf_read->RemainReadLength() > 0)
		{
			int ret = NetCommon::Send(m_sock, m_send_buf_read->GetReadBuf(), m_send_buf_read->RemainReadLength());

			if (ret == SOCKET_ERROR)
			{
				if (NetCommon::Error() == WOULDBLOCK)
				{
					// 缓冲区已经满
					break;
				}
				printf("send error %d", NetCommon::Error());
				m_net_manager->RemoveHandler(m_handle);
				return;
			}
			//
			m_send_buf_read->AddReadLength(ret);
		}
		UnRegisterWriteFD();
		m_send_buf_read->ResetBuf();
	}
}

void Listener::Send(const char *buf, unsigned int len)
{
	MutexLock ml(&m_send_mutex);
	m_send_buf_write->Push(buf, len);
}

void Listener::RegisterWriteFD()
{
	if (m_is_register_write)
	{
		return;
	}
#ifdef WIN32
	FD_SET(m_sock, m_net_manager->GetWriteSet());
#endif // !WIN32

#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
	ev.data.ptr = (void *)this;
	if (epoll_ctl(m_net_manager->GetEpollFD(), EPOLL_CTL_MOD, m_sock, &ev) == -1)
	{
		// 注册写失败
	}
#endif
	MutexLock ml(&m_register_write_mutex);
	m_is_register_write = true;
}

void Listener::UnRegisterWriteFD()
{
	if (!m_is_register_write)
	{
		return;
	}
#ifdef WIN32
	FD_CLR(m_sock, m_net_manager->GetWriteSet());
#endif

#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.ptr = (void *)this;
	if (epoll_ctl(m_net_manager->GetEpollFD(), EPOLL_CTL_MOD, m_sock, &ev) == -1)
	{
		// 反注册写失败
	}
#endif
	MutexLock ml(&m_register_write_mutex);
	m_is_register_write = false;
}


