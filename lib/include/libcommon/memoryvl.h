
#ifndef MEMORY_V_L_H
#define MEMORY_V_L_H

#include "memorypool.h"

/*
	不定长内存池
*/
class MemoryVL
{
public:
	~MemoryVL(){ delete[]m_memory; };

	static MemoryVL &Instance()
	{
		static MemoryVL vl;
		return vl;
	}

	struct MemoryInfo
	{
		unsigned int	index;
		char			*mem;
	};

	bool	Malloc(unsigned int size, MemoryInfo &info);

	bool	Free(MemoryInfo &info);

private:
	MemoryVL();
	unsigned int	m_size;
	MemoryPool		*m_memory;
};

#endif