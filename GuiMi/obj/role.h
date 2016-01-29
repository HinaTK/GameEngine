
#ifndef ROLE_H
#define ROLE_H

#include "obj.h"

class Role : public Obj
{
public:
	Role();
	virtual ~Role();

	void *	operator new(size_t c);
	void	operator delete(void *m);
private:

};

#endif