
#ifndef ROLE_MODULE_H
#define ROLE_MODULE_H

#include "lib/include/db/fieldmanager.h"

class RoleModule : public FieldManager
{
public:
	RoleModule(){};
	virtual ~RoleModule(){};

	bool Save();
};

#endif
