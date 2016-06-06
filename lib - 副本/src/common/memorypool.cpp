
#include <stdlib.h>
#include <stdio.h>
#include "memorypool.h"

MemoryPool::~MemoryPool()
{
	for (unsigned int i = 0; i < m_has_malloc.size(); ++i)
	{
		::free(m_has_malloc[i]);
	}
#ifdef TEST_MEMORY
	printf("alloc time %d, free time %d\n", m_alloc_time, m_free_time);
#endif
}

MemoryPool::MemoryPool( unsigned int size, unsigned int increase /*= 64*/ )
	: m_size(size)
	, m_increase(increase)
#ifdef TEST_MEMORY
	, m_alloc_time(0)
	, m_free_time(0)
	, m_resize_time(0)
#endif // TEST_MEMORY

{
    
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
	
#ifdef TEST_MEMORY
	++m_resize_time;
	printf("resize time %d\n", m_resize_time);
#endif
	return true;
}

void * MemoryPool::Alloc()
{
#ifdef TEST_MEMORY
	++m_alloc_time;
	if (m_alloc_time % 1000 == 0)
	{
		if (m_increase == 128)
		{
			printf("alloc time %d, free time %d\n", m_alloc_time, m_free_time);
		}
		
	}
#endif

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
#ifdef TEST_MEMORY
	++m_free_time;
#endif

    m_pool.push_back(m);
}
