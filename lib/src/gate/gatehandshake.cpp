
#include "gatehandshake.h"
#include "gatelistener.h"
#include "gatethread.h"
#include "common/socketdef.h"
#include "lib/include/base/function.h"

GateHandshake::GateHandshake(SocketThread *t, int size)
: NetHandler(t, NetHandler::HANDSHAKER)
, m_recv_buf(size)
{

}


void GateHandshake::OnCanRead()
{
	if (!RecvBuf())
	{
		Function::Error("gate handshake recv data error");
		m_thread->RemoveHandler(m_handle, m_err, m_err_arg);
	}
}

bool GateHandshake::RecvBuf()
{
	char *buf = NULL;
	int len = 0;
	if (m_recv_buf.GetBufInfo(&buf, len))
	{
		int ret = recv(m_sock, buf, len, 0);
		if (ret <= 0)
		{
			if (ret == SOCKET_ERROR && NetCommon::Error() == WOULDBLOCK)
			{
				return true;
			}
			RETUEN_ERROR_2(NetHandler::DR_RECV_BUF, NetCommon::Error());
		}
		ret = m_recv_buf.AddBufLen(ret);
		if (ret == 0)
		{
			Handshake(m_recv_buf.GetDateLen(), m_recv_buf.GetDataBuf());
			m_recv_buf.ResetBuf();
		}
		else if (ret > 0)
		{
			RETUEN_ERROR(ret);
		}
		return this->RecvBuf();
	}
	RETUEN_ERROR(NetHandler::DR_RECV_FAIL);
}

void GateHandshake::Handshake(unsigned int len, char *buf)
{
	m_thread->ReplaceHandler(m_handle, new GateListener(m_thread, m_recv_buf.GetBufSize()));
}

