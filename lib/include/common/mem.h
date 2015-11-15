
#ifndef _MEM_H
#define _MEM_H

// class Mem
// {
// public:
// 	void *operator new[](size_t s);
// 	void operator delete[](void *m);
// };

namespace Mem
{
	char	*Alloc(unsigned int s);

	void	Free(void *m);
}
#endif