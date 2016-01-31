
#include "listener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"

Listener::Listener(NetManager *manager)
    : NetHandler(manager, NetHandler::LISTENER)
  , m_recv_buf(BASE_BUFFER_LENGTH)
  , m_send_buf_read(new SendBuffer(BASE_BUFFER_LENGTH))
  , m_send_buf_write(new SendBuffer(BASE_BUFFER_LENGTH))
  , m_register_state(-10)
{
}

Listener::~Listener()
{
    if (m_send_buf_read != NULL)
    {
        delete m_send_buf_read;
        m_send_buf_read = NULL;
    }
    if (m_send_buf_write != NULL)
    {
        delete m_send_buf_write;
        m_send_buf_write = NULL;
    }
}

void Listener::OnCanRead()
{
	int ret = RecvBuf();
	if (ret > 0)
	{
		m_net_manager->RemoveHandler(m_handle, ret);
		ret = AnalyzeBuf();
		if (ret > 0)
		{
			m_net_manager->RemoveHandler(m_handle, ret);
		}
		else
		{
			if (m_recv_buf.FreeLength() <= 0)
			{
				m_recv_buf.Resize(16);
			}
		}
	}
}

int Listener::RecvBuf()
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
			return NetHandler::DR_RECV_BUF;
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

	
	return 0;
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
            int ret = send(m_sock, m_send_buf_read->GetReadBuf(), m_send_buf_read->RemainReadLength(), 0);
			if (ret == SOCKET_ERROR)
			{
				if (NetCommon::Error() == WOULDBLOCK)
				{
					// 缓冲区已经满
					break;
				}
                printf("send error %d\n", NetCommon::Error());
				m_net_manager->RemoveHandler(m_handle, NetHandler::DR_SEND_BUF);
				return;
			}
			//
			m_send_buf_read->AddReadLength(ret);
		}
		UnRegisterWriteFD();
		m_send_buf_read->ResetBuf();
	}
}

void Listener::RegisterWriteFD()
{
    MutexLock ml(&m_register_write_mutex);
    if (m_register_state > -10)
    {
        --m_register_state;
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
         printf("RegisterWriteFD error %d\n", m_sock);
	}
#endif
    m_register_state = 0;
}

void Listener::UnRegisterWriteFD()
{
    {
        MutexLock ml(&m_send_mutex);
        if (m_send_buf_write->Length() > 0)
        {
            return;
        }
    }
    MutexLock ml(&m_register_write_mutex);
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
        printf("UnRegisterWriteFD error %d\n", m_sock);
	}
#endif
     m_register_state = -10;
}


