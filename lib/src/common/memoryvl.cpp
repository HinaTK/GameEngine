
#include <stdio.h>
#include "memorypool.h"
#include "memoryvl.h"

static const unsigned int LEN_INT = sizeof(unsigned int);
std::mutex g_init_mutex;

MemoryVL::MemoryVL(unsigned int config[][2], unsigned int num)
: m_size(num)
{
    m_memory = new MemoryPool*[m_size];
	m_mutex = new std::mutex*[m_size];
	for (unsigned int i = 0; i < m_size; ++i)
	{
        m_memory[i] = new MemoryPool(config[i][0] + LEN_INT, config[i][1]);
		m_mutex[i] = new std::mutex;
	}
}

MemoryVL::~MemoryVL()
{
    for (unsigned int i = 0; i < m_size; ++i)
    {
        delete m_memory[i];
		delete m_mutex[i];
        m_memory[i] = NULL;
		m_mutex[i] = NULL;
    }
    delete[]m_memory;
    delete[]m_mutex;
}

void  *MemoryVL::Alloc(unsigned int size)
{
	unsigned int real_size = size + LEN_INT;
	unsigned int i = 0;
	for (; i < m_size; ++i)
	{
        if (real_size <= m_memory[i]->Size())
		{
			break;
		}
	}

    void *mem = 0;

	if (i >= m_size)
	{
        mem = ::malloc(real_size);	// 线程安全，不用加锁
	}
	else
	{
		m_mutex[i]->lock();
        mem = m_memory[i]->Alloc();
		m_mutex[i]->unlock();
	}

    *(unsigned int *)mem = i;
	return ((char *)mem + LEN_INT);
}


bool MemoryVL::Free(void *mem)
{
	char *real_mem = ((char *)mem) - LEN_INT;
	unsigned int index = *(unsigned int*)real_mem;
	if (index >= m_size)
	{
        ::free(real_mem);
	}
	else
	{
		m_mutex[index]->lock();
		m_memory[index]->Free(real_mem);
		m_mutex[index]->unlock();
	}

	return true;
}

