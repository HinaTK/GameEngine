
#ifndef ROLE_MODULE_H
#define ROLE_MODULE_H

#include <vector>
#include "lib/include/db/rolefield.h"
#include "lib/include/thread/threadclass.h"

class RoleModule : public ThreadClass
{
public:
	void Exe(BaseThread *t)
	{
		((DBThread *)t)->GetFieldManager()->Save(&rf);
	}
	RoleField rf;
};

#endif
