
#include "gatelistener.h"
#include "gatethread.h"
#include "lib/include/frame/bufmanager.h"
#include "common/socketdef.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, GateListener, 256);


GateListener::GateListener(SocketThread *t, int size)
: Listener(t, size)
, m_recv_buf(buf_size)
, m_msg_id(-1)
, Recv(&GateListener::Bind)
, m_is_handshake(false)
{

}

GateListener::~GateListener()
{
	if (m_msg_id != -1)
	{
		((GateThread *)m_thread)->DelRole(m_msg_id);
		m_msg_id = -1;
	}
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
		if (ret == 0)
		{
			((GateThread *)m_thread)->Dispatch(m_msg_id, m_handle, m_recv_buf.GetDateLen(), m_recv_buf.GetDataBuf());
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

void GateListener::Bind(unsigned int len, char *buf)
{
	m_thread->Recv(m_msg_index, BaseMsg::MSG_RECV, NetMsg(m_handle, buf, len));
}

void GateListener::Dispatch(unsigned int len, char *buf)
{
	// todo 直接加一种类型BaseMsg::MSG_DISPATCH，发送？
	((GateThread *)m_thread)->Dispatch(m_msg_id, NetMsg(m_handle, buf, len));
}