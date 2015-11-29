
#include <stdlib.h>
#include <stdio.h>
#include "memorypool.h"

MemoryPool::~MemoryPool()
{
	for (unsigned int i = 0; i < m_has_malloc.size(); ++i)
	{
		::free(m_has_malloc[i]);
	}
}

MemoryPool::MemoryPool( unsigned int size, unsigned int increase /*= 64*/ )
	: m_size(size)
	, m_increase(increase)
{
    //Resize();
}

bool MemoryPool::Resize()
{
	void *mem = ::malloc(m_size * m_increase);
	if (NULL == mem)
	{
		return false;
	}
    m_has_malloc.push_back(mem);
	char *unit_mem = (char *)mem;
    void *temp = NULL;
	for (unsigned int i = 0; i < m_increase; ++i)
	{
        temp = (void *)unit_mem;
        m_pool.push_back(temp);
		unit_mem += m_size;
	}
	
	return true;
}

void * MemoryPool::Alloc()
{
	void *mem = NULL;
    if (m_pool.size() <= 0)
	{
		Resize();
	}

    mem = m_pool.back();
    m_pool.pop_back();

    return mem;
}

void MemoryPool::Free(void *m)
{
    m_pool.push_back(m);
}
