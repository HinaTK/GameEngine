
#ifndef _MEM_H
#define _MEM_H

class MemoryVL;
namespace Mem
{
	char	*Alloc(unsigned int s);
	void	Free(void *m);

	char	*TAlloc(unsigned int s);
	void	TFree(void *m);

	MemoryVL *NewMemoryVL();
}
#endif
