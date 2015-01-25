
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufmanager.h"

REGISTER_MEMORYPOOL(memorypool, BufManager, 256);

BufManager::BufManager(unsigned int size)
: m_size(size)
, m_length(0)
{
	Init();
}

//#include <stdio.h>
void BufManager::Init()
{
	m_buf.mem = NULL;
	MemoryVL::Instance().Malloc(m_size, m_buf);
}

BufManager::~BufManager()
{
	if (m_buf.mem != NULL)
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
	memcpy(m_buf.mem + m_length, buf, len);
	m_length += len;
}

bool BufManager::Resize(unsigned int size)
{
	MemoryVL::MemoryInfo info;
	if (!MemoryVL::Instance().Malloc(size, info))
	{
		return false;
	}
	memcpy(info.mem, m_buf.mem, m_length);
	MemoryVL::Instance().Free(m_buf);
	m_buf.mem = info.mem;
	m_buf.index = info.index;
	m_size = size;
	return true;
}

void BufManager::RemoveBuf(unsigned int len)
{
	if (len > m_length)
	{
		return;
	}
	memcpy(m_buf.mem, m_buf.mem + len, m_size - len);
	m_length = m_length - len;
}

void BufManager::ReSetBuf()
{
	m_read_length = 0;
	m_length = 0;
}

