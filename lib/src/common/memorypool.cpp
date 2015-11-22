
#include <stdlib.h>
#include <stdio.h>
#include "memorypool.h"

MemoryPool::MemoryPool()
	: m_init(false)
{
}

MemoryPool::~MemoryPool()
{
    for (game::Vector<void *>::iterator itr = m_has_malloc.Begin(); itr != m_has_malloc.End(); ++itr)
	{
		::free(*itr);
	}
}

MemoryPool::MemoryPool( unsigned int size, unsigned int increase /*= 64*/ )
	: m_size(size)
	, m_increase(increase)
	, m_init(false)
{
	Resize();
	m_init = true;
}

void MemoryPool::Init(unsigned int size, unsigned int increase /*= 64*/)
{
	if (m_init)
	{
		return;
	}
	m_size = size;
	m_increase = increase;
	Resize();
	m_init = true;
}

bool MemoryPool::Resize()
{
	void *mem = ::malloc(m_size * m_increase);
	if (NULL == mem)
	{
		return false;
	}
    m_has_malloc.Push(mem);
	char *unit_mem = (char *)mem;
	for (unsigned int i = 0; i < m_increase; ++i)
	{
		void *save_mem = (void *)unit_mem;
		m_pool.push_back(save_mem);
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
