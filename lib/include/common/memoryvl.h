
#ifndef MEMORY_V_L_H
#define MEMORY_V_L_H

#include "mutex.h"

/*
	不定长内存池
*/
class MemoryPool;
class MemoryVL
{
public:
	MemoryVL(unsigned int config[][2], unsigned int num);
	~MemoryVL();

	struct MemoryInfo
	{
		unsigned int	index;
		char			*mem;
	};

	struct MemoryConfig
	{
		unsigned int size;
		unsigned int num;
	};

	void	*Alloc(unsigned int size);

	bool	Free(void *mem);

private:
	
	unsigned int	m_size;
	MemoryPool		*m_memory;
	std::mutex		*m_mutex;
};

#endif