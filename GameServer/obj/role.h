
#ifndef ROLE_H
#define ROLE_H

#include "obj.h"
#include "common/systemdef.h"

class Role:public Obj
{
public:
	Role();
	~Role();

private:
	NetHandle	m_handle;
};

#endif