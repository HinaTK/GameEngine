
#include <stdlib.h>
#include <stdio.h>
#include "memorypool.h"

MemoryPool::~MemoryPool()
{
    printf("MemoryPool::~MemoryPool() %xd\n", this);
    int i = 1;
    for (std::vector<void *>::iterator itr = m_has_malloc.begin(); itr != m_has_malloc.end(); ++itr)
    {
        ::free(*itr);
        *itr = NULL;
        printf("MemoryPool::~MemoryPool() i= %d\n", i);
        i = i + 1;
    }
    m_has_malloc.clear();
}

MemoryPool::MemoryPool( unsigned int size, unsigned int increase /*= 64*/ )
	: m_size(size)
	, m_increase(increase)
{
    Resize();
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
	for (unsigned int i = 0; i < m_increase; ++i)
	{
        m_pool.push_back((void *)unit_mem);
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
