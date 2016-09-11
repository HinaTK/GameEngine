
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufmanager.h"
#include "lib/include/frame/listener.h"
#include "lib/include/common/mem.h"
#include "lib/include/common/memorypool.h"


SendBuffer::SendBuffer(unsigned int size)
: m_buf(Mem::Alloc(size))
, m_size(size)
, m_length(0)
, m_read_length(0)
{
}


SendBuffer::~SendBuffer()
{
	if (m_buf != NULL)
	{
		Mem::Free(m_buf);
		m_buf = NULL;
	}
}

bool SendBuffer::Resize(unsigned int size)
{
	char *new_buf = Mem::Alloc(m_size + size);
	memcpy(new_buf, m_buf, m_length);
	Mem::Free(m_buf);
	m_buf = new_buf;
	m_size += size;
	return true;
}

void SendBuffer::RemoveBuf(unsigned int len)
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


void SendBuffer::Push(unsigned int buf)
{
	static const int INT_LEN = sizeof(unsigned int);
	if (INT_LEN > (m_size - m_length))
	{
		if (!Resize(m_size + INT_LEN))
		{
			return;
		}
	}
	*(int *)m_buf = buf;
	m_length += INT_LEN;
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

RecvBuffer::RecvBuffer(int buf_size)
: m_buf_size(buf_size)
{
	m_msg.buf = new char[NetCommon::HEADER_LENGTH + 32];
	m_msg.buf_size = NetCommon::HEADER_LENGTH + 32;
	ResetBuf();
}

RecvBuffer::~RecvBuffer()
{
	if (m_msg.buf != NULL)
	{
		delete[] m_msg.buf;
		m_msg.buf = NULL;
	}
}

void RecvBuffer::ResetBuf()
{
	m_msg.msg_len = NetCommon::HEADER_LENGTH;
	m_msg.cur_len = 0;
}

bool RecvBuffer::GetBufInfo(char **buf, int &len)
{
	if (m_msg.cur_len >= m_msg.msg_len)
	{
		return false;
	}
	*buf = m_msg.buf + m_msg.cur_len;
	len = m_msg.msg_len - m_msg.cur_len;
	return true;
}

// 参数由外部保证
// 返回0表示包已经完整

int RecvBuffer::AddBufLen(int len)
{
	m_msg.cur_len += len;
	if (m_msg.cur_len == NetCommon::HEADER_LENGTH)
	{
		NetCommon::Header *header = (NetCommon::Header *)m_msg.buf;
		if (header->msg_len > 0 && header->msg_len < m_buf_size)
		{
			if (header->msg_len > m_msg.buf_size - m_msg.cur_len)
			{
				m_msg.msg_len = m_msg.buf_size = header->msg_len + NetCommon::HEADER_LENGTH;
				char *temp = new char[m_msg.buf_size];
				memcpy(temp, m_msg.buf, m_msg.cur_len);
				delete[] m_msg.buf;
				m_msg.buf = temp;
			}
			else
			{
				m_msg.msg_len += header->msg_len;
			}
		}
		else
		{
			return NetHandler::DR_MSG_TOO_LONG;
		}
	}
	else if (m_msg.cur_len == m_msg.msg_len)
	{
		return 0;
	}
	return -1;
}