
#include "innerlistener.h"
#include "lib/include/base/netcommon.h"
#include "common/socketdef.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, InnerListener, 1);

InnerBuffer::InnerBuffer(InnerListener *listener)
: m_listener(listener)
{
	m_msg.buf = new char[NetCommon::HEADER_LENGTH];
	m_msg.buf_len = NetCommon::HEADER_LENGTH;
}

InnerBuffer::~InnerBuffer()
{
	if (m_msg.buf != NULL)
	{
		delete m_msg.buf;
		m_msg.buf = NULL;
	}
}

void InnerBuffer::ResetBuf()
{
	m_msg.msg_len = 0;
	m_msg.buf_len = 0;
}

bool InnerBuffer::GetBufInfo(char **buf, int &len)
{
	if (m_msg.cur_len >= m_msg.msg_len)
	{
		return false;
	}
	*buf = m_msg.buf + m_msg.cur_len;
	len = m_msg.msg_len - m_msg.buf_len;
	return true;
}

// 参数由外部保证
// 返回0表示包已经完整

int InnerBuffer::AddBufLen(int len)
{
	if (m_msg.cur_len < NetCommon::HEADER_LENGTH)
	{
		m_msg.cur_len += len;
		if (m_msg.cur_len == NetCommon::HEADER_LENGTH)
		{
			NetCommon::Header *header = (NetCommon::Header *)m_msg.buf;
			if (header->msg_len > 0 && header->msg_len < m_listener->buf_size)
			{
				if (header->msg_len > (m_msg.buf_len + NetCommon::HEADER_LENGTH))
				{
					m_msg.msg_len = m_msg.buf_len = header->msg_len + NetCommon::HEADER_LENGTH;
					char *temp = new char[m_msg.buf_len];
					memcpy(temp, m_msg.buf, m_msg.cur_len);
					delete m_msg.buf;
					m_msg.buf = temp;
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
		m_msg.cur_len += len;
		if (m_msg.cur_len == m_msg.msg_len)
		{
			m_listener->Recv(m_listener->m_handle, m_msg.msg_len - NetCommon::HEADER_LENGTH, m_msg.buf + NetCommon::HEADER_LENGTH);
			ResetBuf();
		}
	}
	return 0;
}

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
	m_send_buf->Push(len);
	m_send_buf->Push(buf, len);
}




