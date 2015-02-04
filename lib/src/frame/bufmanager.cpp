
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufmanager.h"

REGISTER_MEMORYPOOL(memorypool, BufManager, 256);

BufManager::BufManager(unsigned int size)
: m_buf(NULL)
, m_size(size)
, m_length(0)
, m_read_length(0)
{
	Init();
}

//#include <stdio.h>
void BufManager::Init()
{
	m_buf = (char *)MemoryVL::Instance().Malloc(m_size);
}

BufManager::~BufManager()
{
	if (m_buf != NULL)
	{
		MemoryVL::Instance().Free(m_buf);
	}
}

void BufManager::Push(const char *buf, unsigned int len)
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

bool BufManager::Resize(unsigned int size)
{
	char *new_buf = (char *)MemoryVL::Instance().Malloc(size);
	memcpy(new_buf, m_buf, m_length);
	MemoryVL::Instance().Free(m_buf);
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
	memcpy(m_buf, m_buf + len, m_size - len);
	m_length = m_length - len;
}

void BufManager::ResetBuf()
{
	m_read_length = 0;
	m_length = 0;
}

