
#include <stdio.h>
#include "memoryvl.h"

static const unsigned int LEN_INT = sizeof(unsigned int);
std::mutex g_init_mutex;

MemoryVL::MemoryVL()
: m_size(0)
{

}

MemoryVL::~MemoryVL()
{
	delete[]m_memory;
	delete[]m_mutex;
}

bool MemoryVL::Init(MEMORY_CONFIG &config)
{
	LOCK(g_init_mutex);
	MEMORY_CONFIG::iterator itr = config.begin();
	m_size = config.size();
	m_memory = new MemoryPool[m_size];
	m_mutex = new std::mutex[m_size];
	unsigned int i = 0;
	for (; itr != config.end() && i < m_size; ++itr, ++i)
	{
		m_memory[i].Init(itr->size + LEN_INT, itr->num);
	}
	UNLOCK(g_init_mutex);
	return true;
}

void  *MemoryVL::Malloc(unsigned int size)
{
	unsigned int real_size = size + LEN_INT;
	unsigned int i = 0;
	for (; i < m_size; ++i)
	{
		if (real_size <= m_memory[i].Size())
		{
			break;
		}
	}

	char *mem = 0;

	if (i >= m_size)
	{
		mem = (char *)::malloc(real_size);	// �̰߳�ȫ�����ü���
	}
	else
	{
		LOCK(m_mutex[i]);
		mem = (char *)m_memory[i].Alloc();	
		UNLOCK(m_mutex[i]);
	}

	*(unsigned int *)mem = i;
	return (mem + LEN_INT);
}


bool MemoryVL::Free(void *mem)
{
	char *real_mem = ((char *)mem) - LEN_INT;
	unsigned int index = *(unsigned int*)real_mem;
	if (index >= m_size)
	{
		::free(mem);
	}
	else
	{
		LOCK(m_mutex[index]);
		m_memory[index].Free(mem);
		UNLOCK(m_mutex[index]);
	}

	return true;
}
