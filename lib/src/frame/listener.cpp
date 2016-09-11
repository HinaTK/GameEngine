
#include "listener.h"
#include "bufmanager.h"
#include "common/socketdef.h"
#include "lib/include/base/function.h"
#include "lib/include/base/netcommon.h"

#define REGISTER_STATE -10

Listener::Listener(SocketThread *t, int size)
	: NetHandler(t, NetHandler::LISTENER)
	, m_send_buf(new SendBuffer(BASE_BUFFER_LENGTH))
	, m_register_state(REGISTER_STATE)
	, buf_size(size)
{
}

Listener::~Listener()
{
    if (m_send_buf != NULL)
    {
        delete m_send_buf;
        m_send_buf = NULL;
    }
}

void Listener::OnCanRead()
{
	if (!RecvBuf())
	{
		m_thread->RemoveHandler(m_handle, m_err, m_err_arg);
	}
}

void Listener::OnCanWrite()
{
	while (m_send_buf->RemainReadLength() > 0)
	{
		int ret = send(m_sock, m_send_buf->GetReadBuf(), m_send_buf->RemainReadLength(), 0);
		if (ret == SOCKET_ERROR)
		{
			if (NetCommon::Error() == WOULDBLOCK)
			{
				// 缓冲区已经满
				break;
			}
			Function::Info("Send error %d", NetCommon::Error());
			m_thread->RemoveHandler(m_handle, NetHandler::DR_SEND_BUF);
			return;
		}
		//
		m_send_buf->AddReadLength(ret);
	}
	m_send_buf->ResetBuf();
	UnRegisterWriteFD();
}

void Listener::RegisterWriteFD()
{
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
    if (m_send_buf->Length() > 0)
    {
        return;
    }

	m_thread->SetCanNotWrite(this);
	m_register_state = REGISTER_STATE;
}

void Listener::Send(const char *buf, unsigned int len)
{
	m_send_buf->Push(len);
	m_send_buf->Push(buf, len);
}


