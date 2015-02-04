
#include <stdio.h>
#include "memoryvl.h"
#include "commonconfig.h"

static const unsigned int LEN_INT = sizeof(unsigned int);
static CommonConfig::MEMORY_VL_VECTOR mv = CommonConfig::Instance().GetMemoryVLVector();
Mutex g_init_mutex;
MemoryVL::MemoryVL()
: m_size(0)
{
	MutexLock lock(&g_init_mutex);
	CommonConfig::MEMORY_VL_VECTOR::iterator itr = mv.begin();
	m_size = mv.size();
	m_memory = new MemoryPool[m_size];
	m_mutex = new Mutex[m_size];
	unsigned int i = 0;
	for (; itr != mv.end() && i < m_size; ++itr, ++i)
	{
		m_memory[i].Init(itr->size + LEN_INT , itr->num);
	}
}

MemoryVL::~MemoryVL()
{
	delete[]m_memory;
	delete[]m_mutex;
}

void  *MemoryVL::Malloc(unsigned int size)
{
	unsigned real_size = size + LEN_INT;
	unsigned int i = 0;
	for (; i < m_size; ++i)
	{
		if (real_size < mv[i].size)
		{
			break;
		}
	}
	if (i >= m_size)
	{
		return NULL;
	}
	char *mem = 0;
	{
		MutexLock lock(&m_mutex[i]);
		mem = (char *)m_memory[i].Alloc();
	}
	
	return (mem + LEN_INT);
}


bool MemoryVL::Free(void *mem)
{
	char *real_mem = ((char *)mem) - LEN_INT;
	unsigned int index = *(unsigned int*)real_mem;
	if (index >= m_size)
	{
		//::free(info.mem);
		return false;
	}
	{
		MutexLock lock(&m_mutex[index]);
		m_memory[index].Free(mem);
	}
	
	return true;
}
