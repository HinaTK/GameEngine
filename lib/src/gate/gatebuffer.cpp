
#include "gatebuffer.h"
#include "lib/include/frame/listener.h"

GateBuffer::GateBuffer(Listener *listener)
: m_listener(listener)
{
	m_msg.buf = new char[NetCommon::HEADER_LENGTH];
	m_msg.buf_len = NetCommon::HEADER_LENGTH;
}

GateBuffer::~GateBuffer()
{
	if (m_msg.buf != NULL)
	{
		delete m_msg.buf;
		m_msg.buf = NULL;
	}
}

void GateBuffer::ResetBuf()
{
	m_msg.msg_len = 0;
	m_msg.cur_len = 0;
}

bool GateBuffer::GetBufInfo(char **buf, int &len)
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

int GateBuffer::AddBufLen(int len)
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
