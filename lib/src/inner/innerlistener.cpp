
#include "innerlistener.h"
#include "lib/include/base/netcommon.h"
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
		if (ret == 0)
		{
			// todo dispatch data
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



