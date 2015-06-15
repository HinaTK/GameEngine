
#ifndef MEMORY_V_L_H
#define MEMORY_V_L_H

#include <vector>
#include "memorypool.h"
#include "mutex.h"

/*
	�������ڴ��
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

	struct MemoryConfig
	{
		unsigned int size;
		unsigned int num;
	};

	typedef std::vector<MemoryConfig> MEMORY_CONFIG;

	bool	Init(MEMORY_CONFIG &config);

	void	*Malloc(unsigned int size);

	bool	Free(void *mem);

private:
	MemoryVL();
	unsigned int	m_size;
	MemoryPool		*m_memory;
	std::mutex		*m_mutex;
};

#endif