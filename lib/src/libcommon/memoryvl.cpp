
#include <stdio.h>
#include "memoryvl.h"
#include "commonconfig.h"

// static const unsigned int sizes[] = { 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144 };
// static const int nums[] = { 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1 };
static CommonConfig::MEMORY_VL_VECTOR mv = CommonConfig::Instance().GetMemoryVLVector();
MemoryVL::MemoryVL()
: m_size(0)
{
	CommonConfig::MEMORY_VL_VECTOR::iterator itr = mv.begin();
	m_size = mv.size();
	m_memory = new MemoryPool[m_size];
	unsigned int i = 0;
	for (; itr != mv.end() && i < m_size; ++itr, ++i)
	{
		m_memory[i].Init(itr->size, itr->num);
	}
}

bool MemoryVL::Malloc(unsigned int size, MemoryInfo &info)
{
	unsigned int i = 0;
	for (; i < m_size; ++i)
	{
		if (size < mv[i].size)
		{
			break;
		}
	}
	if (i >= m_size)
	{
		return false;
	}

	info.index = i;
	info.mem = (char *)m_memory[i].Alloc();
	return true;
}


bool MemoryVL::Free(MemoryInfo &info)
{
	if (info.index >= m_size)
	{
		//::free(info.mem);
		return false;
	}

	m_memory[info.index].Free(info.mem);
	return true;
}
