
#include <stdio.h>
#include <stdlib.h>
#include "memorypool.h"

MemoryPool::MemoryPool()
: m_init(false)
{

}

MemoryPool::~MemoryPool()
{
	for (std::vector<void *>::iterator itr = m_has_malloc.begin(); itr != m_has_malloc.end(); ++itr)
	{
		free(*itr);
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

bool MemoryPool::Resize()
{
	void *mem = malloc(m_size * m_increase);
	if (mem == NULL)
	{
		return false;
	}
	m_has_malloc.push_back(mem);
	char *unit_mem = (char *)mem;
	for (unsigned int i = 0; i < m_increase; ++i)
	{
		m_pool.push_back(unit_mem);
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
