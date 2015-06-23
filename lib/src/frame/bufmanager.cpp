
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufmanager.h"
#include "lib/include/common/memorypool.h"

REGISTER_MEMORYPOOL(memorypool, BufManager, 256);
REGISTER_MEMORYPOOL(memorypool, SendBuffer, 256);

BufManager::BufManager(unsigned int size)
: m_buf(new Mem[(unsigned int)size])
, m_size(size)
, m_length(0)
{
}


BufManager::~BufManager()
{
	if (m_buf != NULL)
	{
		delete []m_buf;
	}
}

bool BufManager::Resize(unsigned int size)
{
	Mem *new_buf = new Mem[size];
	memcpy(new_buf, m_buf, m_length);
	delete []m_buf;
	m_buf = new_buf;
	m_size = size;
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


// 
// RecvBufffer::~RecvBufffer()
// {
// 
// }
// 
// RecvBufffer::RecvBufffer(unsigned int size /*= 64*/)
// : BufManager(size)
// {
// 
// }

SendBuffer::~SendBuffer()
{

}

SendBuffer::SendBuffer(unsigned int size /*= 64*/)
: BufManager(size)
, m_read_length(0)
{

}

// �ɲ��ɱ���buf��ָ�룬�����ڴ濽������
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
