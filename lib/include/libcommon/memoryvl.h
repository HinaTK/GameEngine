
#ifndef MEMORY_V_L_H
#define MEMORY_V_L_H

#include "memorypool.h"
#include "mutex.h"

/*
	不定长内存池
*/
class MemoryVL
{
public:
	~MemoryVL();

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

	void	*Malloc(unsigned int size);

	bool	Free(void *mem);

private:
	MemoryVL();
	unsigned int	m_size;
	MemoryPool		*m_memory;
	Mutex			*m_mutex;
};

#endif