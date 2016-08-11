
#include "gatelistener.h"
#include "lib/include/frame/netcommon.h"
#include "lib/include/frame/netmanager.h"
#include "common/socketdef.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, GateListener, 256);

GateListener::GateListener(SocketThread *t, int size)
: Listener(t, size)
, m_recv_buf(this)
{

}

bool GateListener::RecvBuf()
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
		if (ret > 0)
		{
			RETUEN_ERROR(ret);
		}
		return this->RecvBuf();
	}
	RETUEN_ERROR(NetHandler::DR_RECV_FAIL);
}


void GateListener::Send( const char *buf, unsigned int len )
{
	m_send_buf->Push((const char *)&len, NetCommon::HEADER_LENGTH);
	m_send_buf->Push(buf, len);
}




