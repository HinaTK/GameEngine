
#include "gatelistener.h"
#include "lib/include/frame/bufmanager.h"
#include "common/socketdef.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, GateListener, 256);

GateBuffer::GateBuffer(GateListener *listener)
: m_listener(listener)
, m_head_len(0)
{

}

GateBuffer::~GateBuffer()
{

}

void GateBuffer::ResetBuf()
{
	m_head_len = 0;
	m_msg.msg_len = 0;
	m_msg.buf_len = 0;
}

bool GateBuffer::GetBufInfo(char **buf, int &len)
{
	if (m_head_len < NetCommon::HEADER_LENGTH)
	{
		*buf = m_header + m_head_len;
		len = NetCommon::HEADER_LENGTH - m_head_len;
		return true;
	}

	if (m_msg.buf_len >= m_msg.msg_len)
	{
		return false;
	}
	*buf = m_msg.buf;
	len = m_msg.msg_len - m_msg.buf_len;
	return true;
}

// 参数由外部保证
// 返回0表示包已经完整

int GateBuffer::AddBufLen(int len)
{
	if (m_head_len < NetCommon::HEADER_LENGTH)
	{
		m_head_len += len;
		if (m_head_len == NetCommon::HEADER_LENGTH)
		{
			NetCommon::Header *header = (NetCommon::Header *)m_header;
			if (header->msg_len > 0 && header->msg_len < m_listener->buf_size)
			{
				if (header->msg_len > m_msg.buf_len)
				{
					char *temp = new char[header->msg_len];
					memcpy(temp, m_msg.buf, m_msg.cur_len);
					delete m_msg.buf;
					m_msg.buf = temp;
					m_msg.msg_len = header->msg_len;
				}
			}
			else
			{
				return NetHandler::DR_MSG_TOO_LONG;
			}
		}
	}
	else
	{
		m_msg.buf_len += len;
		if (m_msg.buf_len == m_msg.msg_len)
		{
			m_listener->GetThread()->Recv(m_listener->m_msg_index, BaseMsg::MSG_RECV, NetMsg(m_listener->m_handle, m_msg.buf, m_msg.msg_len));
			ResetBuf();
		}
	}
	return 0;
}


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
	m_send_buf->Push(len);
	m_send_buf->Push(buf, len);
}

