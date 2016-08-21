﻿
#include "innerlistener.h"
#include "lib/include/base/netcommon.h"
#include "common/socketdef.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, InnerListener, 1);

InnerBuffer::InnerBuffer(InnerListener *listener)
: m_listener(listener)
, m_head_len(0)
{

}

InnerBuffer::~InnerBuffer()
{

}

void InnerBuffer::ResetBuf()
{
	m_head_len = 0;
	m_msg.msg_len = 0;
	m_msg.buf_len = 0;
}

bool InnerBuffer::GetBufInfo(char **buf, int &len)
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

int InnerBuffer::AddBufLen(int len)
{
	if (m_head_len < NetCommon::HEADER_LENGTH)
	{
		m_head_len += len;
		if (m_head_len == NetCommon::HEADER_LENGTH)
		{
			NetCommon::Header *header = (NetCommon::Header *)m_header;
			if (m_listener->buf_size == 0 || (header->msg_len > 0 && header->msg_len < m_listener->buf_size))
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
	m_send_buf->Push((const char *)&len, NetCommon::HEADER_LENGTH);
	m_send_buf->Push(buf, len);
}




