
#include "innerlistener.h"
#include "lib/include/frame/netcommon.h"
#include "lib/include/frame/netmanager.h"
#include "common/socketdef.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, InnerListener, 1);

InnerListener::InnerListener(SocketThread *t, int size)
: Listener(t)
, buf_size(size)
, m_recv_buf(this)
{

}

bool InnerListener::RecvBuf()
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


void InnerListener::Send( const char *buf, unsigned int len )
{
	MutexLock ml(&m_send_mutex);
	m_send_buf_write->Push((const char *)&len, NetCommon::HEADER_LENGTH);
	m_send_buf_write->Push(buf, len);
}




