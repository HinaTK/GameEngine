
#include "mem.h"
#include "memoryvl.h"

unsigned int mem_config[][2] = { 
	{ 16,		128 }, 
	{ 32,		128 },
	{ 64,		128 },
	{ 128,		128 },
	{ 256,		64 },
	{ 512,		64 },
	{ 1024,		32 },
	{ 2048,		32 },
	{ 4096,		16 },
	{ 8192,		16 },
	{ 16384,	8 },
	{ 32768,	4 },
	{ 65536,	2 },
	{ 131072,	2 },
	{ 262144,   2 }
};
static MemoryVL g_mem_pool(mem_config, 15);

// void * Mem::operator new[](size_t s)
// {
// 	return g_mem_pool.Alloc((unsigned int)s);
// }
// 
// void Mem::operator delete[](void *m)
// {
// 	g_mem_pool.Free(m);
// }

char * Mem::Alloc(unsigned int s)
{
	return (char *)g_mem_pool.Alloc(s);
}

void Mem::Free(void *m)
{
	g_mem_pool.Free(m);
}
