
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufmanager.h"
#include "netmanager.h"
#include "lib/include/frame/listener.h"
#include "lib/include/common/mem.h"
#include "lib/include/common/memorypool.h"

REGISTER_MEMORYPOOL(memorypool, RecvBuffer, 256);
REGISTER_MEMORYPOOL(memorypool, SendBuffer, 256);

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



RecvBuffer::~RecvBuffer()
{

}

RecvBuffer::RecvBuffer(unsigned int size /*= 64*/)
: BufManager(size)
{

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

TestBuffer::TestBuffer(Listener *listener)
: m_listener(listener)
, m_header_len(0)
, m_buf_len(NetCommon::HEADER_LENGTH)
, m_msg(NULL)
{
	
}

TestBuffer::~TestBuffer()
{
	if (m_msg != NULL)
	{
		delete m_msg;
		m_msg = NULL;
	}
}

void TestBuffer::ResetBuf()
{
	m_header_len = 0;
	m_buf_len = NetCommon::HEADER_LENGTH;
	m_msg = NULL;
}

bool TestBuffer::GetBufInfo(char **buf, int &len)
{
	if (m_header_len < NetCommon::HEADER_LENGTH)
	{
		*buf = (char *)m_header[m_header_len];
		len = NetCommon::HEADER_LENGTH - m_header_len;
		return true;
	}
	
	if (m_buf_len >= m_msg->length)
	{
		return false;
	}
	*buf = (char *)m_msg->data[m_buf_len];
	len = m_msg->length - m_buf_len;
	return true;
}

// 参数由外部保证
// 返回true表示包已经完整

bool TestBuffer::AddBufLen(int len)
{
	if (m_header_len < NetCommon::HEADER_LENGTH)
	{
		m_header_len += len;
		if (m_header_len == NetCommon::HEADER_LENGTH)
		{
			NetCommon::Header *header = (NetCommon::Header *)m_header;
			// todo 判断消息头长度的合法性
			m_msg = m_listener->GetThread()->CreateGameMsg(m_listener->m_msg_index, BaseMsg::MSG_RECV, m_listener->m_handle, NetCommon::HEADER_LENGTH + header->msg_len);
			*(int *)m_msg->data =header->msg_len;
		}
	}
	else
	{
		if (m_buf_len < m_msg->length)
		{
			m_buf_len += len;
			if (m_buf_len == m_msg->length)
			{
				return true;
			}
		}
	}
	return false;
}

void TestBuffer::Send()
{
	m_listener->GetThread()->PushGameMsg(m_msg);
	ResetBuf();
}
