
#include "gatebuffer.h"
#include "lib/include/frame/listener.h"

GateBuffer::GateBuffer(Listener *listener)
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
			m_listener->Recv(m_listener->m_handle, m_msg.msg_len, m_msg.buf);
			ResetBuf();
		}
	}
	return 0;
}
