
#include <stdio.h>
#include "memorypool.h"
#include "memoryvl.h"

static const unsigned int LEN_INT = sizeof(unsigned int);
std::mutex g_init_mutex;

MemoryVL::MemoryVL(unsigned int config[][2], unsigned int num)
: m_size(num)
{
    m_memory = new MemoryPool*[m_size];
	m_mutex = new std::mutex[m_size];
	for (unsigned int i = 0; i < m_size; ++i)
	{
        m_memory[i] = new MemoryPool(config[i][0] + LEN_INT, config[i][1]);
	}

}

MemoryVL::~MemoryVL()
{
    for (int i = 0; i < m_size; ++i)
    {
        delete m_memory[i];
        m_memory[i] = NULL;
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

	char *mem = 0;

	if (i >= m_size)
	{
		mem = (char *)::malloc(real_size);	// 线程安全，不用加锁
	}
	else
	{
		LOCK(m_mutex[i]);
        mem = (char *)m_memory[i]->Alloc();
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
        m_memory[index]->Free(mem);
		UNLOCK(m_mutex[index]);
	}

	return true;
}
