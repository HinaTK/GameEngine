
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufmanager.h"
#include "netmanager.h"
#include "lib/include/frame/listener.h"
#include "lib/include/common/mem.h"
#include "lib/include/common/memorypool.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, RecvBuffer, 256);

BufManager::BufManager(unsigned int size)
: m_buf(Mem::Alloc(size))
, m_size(size)
, m_length(0)
{
}


BufManager::~BufManager()
{
	if (m_buf != NULL)
	{
		Mem::Free(m_buf);
		m_buf = NULL;
	}
}

bool BufManager::Resize(unsigned int size)
{
	char *new_buf = Mem::Alloc(m_size + size);
	memcpy(new_buf, m_buf, m_length);
	Mem::Free(m_buf);
	m_buf = new_buf;
	m_size += size;
	return true;
}

void BufManager::RemoveBuf(unsigned int len)
{
	if (len > m_length)
	{
		return;
	}
	
	if (len == m_length)
	{
		m_length = 0;
	}
	else
	{
		memcpy(m_buf, m_buf + len, m_size - len);
		m_length = m_length - len;
	}
}

SendBuffer::~SendBuffer()
{

}

SendBuffer::SendBuffer(unsigned int size /*= 64*/)
: BufManager(size)
, m_read_length(0)
{

}

// 可不可保存buf的指针，减少内存拷贝？！
void SendBuffer::Push(const char *buf, unsigned int len)
{
	if (len > (m_size - m_length))
	{
		if (!Resize(m_size + len))
		{
			return;
		}
	}
	memcpy(m_buf + m_length, buf, len);
	m_length += len;
}

void SendBuffer::ResetBuf()
{
	m_read_length = 0;
	m_length = 0;
}

RecvBuffer::RecvBuffer(Listener *listener)
: m_listener(listener)
, m_head_len(0)
, m_buf_len(0)
{
	
}

RecvBuffer::~RecvBuffer()
{
	
}

void RecvBuffer::ResetBuf()
{
	m_head_len = 0;
	m_buf_len = 0;
	m_msg.length = 0;
	m_msg.data = NULL;
}

bool RecvBuffer::GetBufInfo(char **buf, int &len)
{
	if (m_head_len < NetCommon::HEADER_LENGTH)
	{
		*buf = m_header + m_head_len;
		len = NetCommon::HEADER_LENGTH - m_head_len;
		return true;
	}
	
	if (m_buf_len >= (int)m_msg.length)
	{
		return false;
	}
	*buf = m_msg.data;
	len = m_msg.length - m_buf_len;
	return true;
}

// 参数由外部保证
// 返回0表示包已经完整

int RecvBuffer::AddBufLen(int len)
{
	if (m_head_len < NetCommon::HEADER_LENGTH)
	{
		m_head_len += len;
		if (m_head_len == NetCommon::HEADER_LENGTH)
		{
			NetCommon::Header *header = (NetCommon::Header *)m_header;
			if (m_listener->buf_size == 0 || (header->msg_len > 0 && header->msg_len < m_listener->buf_size))
			{
				m_msg.msg_index = m_listener->m_msg_index;
				m_msg.msg_type = BaseMsg::MSG_RECV;
				m_msg.handle = m_listener->m_handle;
				m_msg.length = header->msg_len;
				m_msg.data = m_listener->GetThread()->CreateData(header->msg_len);
			}
			else
			{
				return NetHandler::DR_MSG_TOO_LONG;
			}
		}
	}
	else
	{
		m_buf_len += len;
		if (m_buf_len == m_msg.length)
		{
			m_listener->GetThread()->PushGameMsg(m_msg);
			ResetBuf();
		}
	}
	return 0;
}
