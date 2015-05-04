
#include <stdio.h>
#include "memoryvl.h"

static const unsigned int LEN_INT = sizeof(unsigned int);
Mutex g_init_mutex;

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
	MutexLock lock(&g_init_mutex);
	MEMORY_CONFIG::iterator itr = config.begin();
	m_size = config.size();
	m_memory = new MemoryPool[m_size];
	m_mutex = new Mutex[m_size];
	unsigned int i = 0;
	for (; itr != config.end() && i < m_size; ++itr, ++i)
	{
		m_memory[i].Init(itr->size + LEN_INT, itr->num);
	}

	return true;
}

void  *MemoryVL::Malloc(unsigned int size)
{
	unsigned int real_size = size + LEN_INT;
	unsigned int i = 0;
	for (; i < m_size; ++i)
	{
		if (real_size < m_memory[i].Size())
		{
			break;
		}
	}
	if (i >= m_size)
	{
		return new char[real_size];
	}
	char *mem = 0;
	{
		MutexLock lock(&m_mutex[i]);
		mem = (char *)m_memory[i].Alloc();
		*(unsigned int *)mem = i;
	}

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
		MutexLock lock(&m_mutex[index]);
		m_memory[index].Free(mem);
	}

	return true;
}
