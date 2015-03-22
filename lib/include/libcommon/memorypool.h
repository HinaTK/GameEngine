
#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include "lib/gamevector.h"

class MemoryPool
{
public:
	MemoryPool();
	MemoryPool(unsigned int size, unsigned int increase = 64);
	~MemoryPool();
	void *	Alloc();
	void	Free(void *m);
	void	Init(unsigned int size, unsigned int increase = 64);
private:
	bool	Resize();

private:
	unsigned int m_size;
	unsigned int m_increase;

	game::Vector<void *> m_pool;
	game::Vector<void *> m_has_malloc;
	bool		 m_init;
};



#define REGISTER_MEMORYPOOL(PoolNameSpace, ClassName, IncreaseNum) \
namespace PoolNameSpace\
{\
	MemoryPool g_##ClassName##_mem_pool(sizeof(ClassName), IncreaseNum);\
}\
	void *ClassName::operator new(size_t size)\
{\
	void *mem = PoolNameSpace::g_##ClassName##_mem_pool.Alloc();\
	return mem;\
}\
	void ClassName::operator delete(void *m)\
{\
	PoolNameSpace::g_##ClassName##_mem_pool.Free(m);\
}

#endif
