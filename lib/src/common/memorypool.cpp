
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
	for (unsigned int i = 0; i < m_pool.size(); ++i)
	{
		if (m_pool[i] == NULL)
		{
			printf("fuck\n");
		}
	}

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
	
	for (unsigned int i = 0; i < m_pool.size(); ++i)
	{
		if (m_pool[i] == NULL)
		{
			printf("fuck\n");
		}
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
	if (m == NULL)
	{
		printf("fuck\n");
	}
	for (unsigned int i = 0; i < m_pool.size(); ++i)
	{
		if (m_pool[i] == NULL)
		{
			printf("fuck\n");
		}
	}
	m_pool.push_back(m);

}
