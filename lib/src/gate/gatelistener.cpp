
#include "gatelistener.h"
#include "gatethread.h"
#include "lib/include/frame/bufmanager.h"
#include "common/socketdef.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, GateListener, 256);


GateListener::GateListener(SocketThread *t, time_t now, int size)
: Listener(t, size)
, m_recv_buf(this)
, m_msg_id(-1)
, Recv(&GateListener::Handshake)
, m_is_handshake(false)
, m_build_time(now)
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
	m_send_buf->Push(len);
	m_send_buf->Push(buf, len);
}

// void GateListener::Recv(NetHandle handle, unsigned int len, char *buf)
// {
// 	((GateThread *)m_thread)->Dispatch(m_msg_id, NetMsg(handle, buf, len));
// }

/*
	* 这样做的有风险，就是一旦出错，多个对象读取同一个队列，导致数据异常
*/

void GateListener::Handshake(unsigned int len, char *buf)
{
	Recv = &GateListener::Bind;
	m_is_handshake = true;
}

void GateListener::Bind(unsigned int len, char *buf)
{
	m_thread->Recv(m_msg_index, BaseMsg::MSG_RECV, NetMsg(m_handle, buf, len));
// 	char *data = m_thread->GetManager()->CreateData(((GateThread *)m_thread)->GetGlobal(), len + sizeof(NetHandle));
// 	if (data != NULL)
// 	{
// 		*(NetHandle *)data = m_handle;
// 		memcpy(data + sizeof(NetHandle), buf, len);
// 		m_thread->GetManager()->SendMsg(((GateThread *)m_thread)->GetGlobal(), GateThread::GATE_ROLE_BIND, len + sizeof(NetHandle), data, m_thread->GetID());
// 	}
}

void GateListener::Dispatch(unsigned int len, char *buf)
{
	((GateThread *)m_thread)->Dispatch(m_msg_id, NetMsg(m_handle, buf, len));
}
