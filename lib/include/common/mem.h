
#ifndef _MEM_H
#define _MEM_H

class Mem
{
public:
	void *operator new[](size_t c);
	void operator delete[](void *m);
};

#endif