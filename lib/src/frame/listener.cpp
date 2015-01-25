
#include "listener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"

REGISTER_MEMORYPOOL(memorypool, Listener, 256);

void Listener::OnCanRead()
{
	if (!RecvBuf() || !AnalyzeBuf())
	{
		NetCommon::Close(m_net_id);
		m_net_manager->RemoveHandler(m_handle);
	}
}

bool Listener::RecvBuf()
{
	do
	{
		int ret = recv(m_net_id, m_recv_buf.GetFreeBuf(), m_recv_buf.FreeLength(), 0);
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
		NetCommon::Ioctl(m_net_id, FIONREAD, &arg);
		if (arg == 0)
		{
			break;
		}
		if (arg > m_recv_buf.FreeLength())
		{
			// Ô¤Áô¶à16×Ö½Ú
			m_recv_buf.Resize(arg - m_recv_buf.FreeLength() + 16);
		}

	} while (true);
	return true;
}

bool Listener::AnalyzeBuf()
{
	const char *buf = m_recv_buf.GetBuf();
	NetCommon::Header *header = (NetCommon::Header *)buf;
	while (header->msg_len <= (int)m_recv_buf.Length() && !m_recv_buf.IsEmpty() && header->msg_len > NetCommon::HEADER_LENGTH)
	{
		m_net_manager->GetMsgQueue()->Push(m_net_id, buf + NetCommon::HEADER_LENGTH, header->msg_len - NetCommon::HEADER_LENGTH);
		m_recv_buf.RemoveBuf(header->msg_len);
		header = (NetCommon::Header *)buf;
	}
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
				BufManager *temp_buf = m_send_buf_read;
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
			int ret = NetCommon::Send(m_net_id, m_send_buf_read->GetReadBuf(), m_send_buf_read->RemainReadLength());

			if (ret == SOCKET_ERROR)
			{
				if (NetCommon::Error() == WOULDBLOCK)
				{
					// »º³åÇøÒÑ¾­Âú
					break;
				}

				NetCommon::Close(m_net_id);
				m_net_manager->RemoveHandler(m_handle);
				return;
			}
			//
			m_send_buf_read->AddReadLength(ret);
		}
		UnRegisterWriteFD();
		m_send_buf_read->ReSetBuf();
	}
}

void Listener::RegisterWriteFD()
{
	if (m_is_register_write)
	{
		return;
	}
#ifdef WIN32
	FD_SET(m_net_id, m_net_manager->GetWriteSet());
#endif // !WIN32

#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
	ev.data.ptr = (void *)this;
	if (epoll_ctl(m_net_manager->GetEpollFD(), EPOLL_CTL_MOD, m_net_id, &ev) == -1)
	{
		// ×¢²áÐ´Ê§°Ü
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
	FD_CLR(m_net_id, m_net_manager->GetWriteSet());
#endif

#ifdef __unix
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.ptr = (void *)this;
	if (epoll_ctl(m_net_manager->GetEpollFD(), EPOLL_CTL_MOD, m_net_id, &ev) == -1)
	{
		// ·´×¢²áÐ´Ê§°Ü
	}
#endif
	MutexLock ml(&m_register_write_mutex);
	m_is_register_write = false;
}

void Listener::Send(const char *buf, unsigned int len)
{
	MutexLock ml(&m_send_mutex);
	m_send_buf_read->Push(buf, len);
}

