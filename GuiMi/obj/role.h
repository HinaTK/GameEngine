
#ifndef ROLE_H
#define ROLE_H

#include "obj.h"

class Role : public Obj
{
public:
	Role(unsigned int index);
	virtual ~Role();

	void *	operator new(size_t c);
	void	operator delete(void *m);
private:

	unsigned int m_msg_index;

};

#endif