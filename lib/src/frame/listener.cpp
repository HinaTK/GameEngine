
#include "listener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"

#define REGISTER_STATE -10

Listener::Listener(SocketThread *t)
	: NetHandler(t, NetHandler::LISTENER)
	, m_send_buf_read(new SendBuffer(BASE_BUFFER_LENGTH))
	, m_send_buf_write(new SendBuffer(BASE_BUFFER_LENGTH))
	, m_register_state(REGISTER_STATE)
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
	if (!RecvBuf() || !AnalyzeBuf())
	{
		m_thread->RemoveHandler(m_handle, m_err, m_err_arg);
	}
}

bool Listener::RecvBuf()
{
// 	unsigned long arg = 32;
// 	do
// 	{
// 		if (arg > m_recv_buf.FreeLength())
// 		{
// 			m_recv_buf.Resize(arg - m_recv_buf.FreeLength());
// 		}
// 
// 		int ret = recv(m_sock, m_recv_buf.GetFreeBuf(), m_recv_buf.FreeLength(), 0);
// 		if (ret <= 0)
// 		{
// 			if (ret == SOCKET_ERROR && NetCommon::Error() == WOULDBLOCK)
// 			{
// 				break;
// 			}
// 			m_err = NetHandler::DR_RECV_BUF;
// 			return false;
// 		}
// 		m_recv_buf.AddLength(ret);
// 		
// 		NetCommon::Ioctl(m_sock, FIONREAD, &arg);
// 		if (arg == 0)
// 		{
// 			break;
// 		}
// 	} while (true);

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
            int ret = send(m_sock, m_send_buf_read->GetReadBuf(), m_send_buf_read->RemainReadLength(), 0);
			if (ret == SOCKET_ERROR)
			{
				if (NetCommon::Error() == WOULDBLOCK)
				{
					// 缓冲区已经满
					break;
				}
                printf("send error %d\n", NetCommon::Error());
				m_thread->RemoveHandler(m_handle, NetHandler::DR_SEND_BUF);
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
	if (m_register_state > REGISTER_STATE)
    {
        --m_register_state;
        return;
    }

	m_thread->SetCanWrite(this);
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
	m_thread->SetCanNotWrite(this);
	m_register_state = REGISTER_STATE;
}


