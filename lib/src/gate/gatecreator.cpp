
#include "gatecreator.h"
#include "lib/include/frame/bufmanager.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, GateCreator, 256);

GateCreator::GateCreator(SocketThread *t, int size)
: Listener(t, size)
, m_recv_buf(this)
{

}

bool GateCreator::RecvBuf()
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

void GateCreator::Send( const char *buf, unsigned int len )
{
	m_send_buf->Push(len);
	m_send_buf->Push(buf, len);
}

void GateCreator::Recv(NetHandle handle, unsigned int len, char *buf)
{
	// todo 加上句柄，和线程id
	// m_thread->GetManager()->SendMsg()
}