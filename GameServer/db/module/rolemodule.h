
#ifndef ROLE_MODULE_H
#define ROLE_MODULE_H

#include <vector>
#include "db/dbmodule.h"
#include "lib/include/db/rolefield.h"

class RoleModule : public DBModule
{
public:
	~RoleModule()
	{
		for (std::vector<RoleField *>::iterator itr = rold_list.begin(); itr != rold_list.end(); ++itr)
		{
			delete *itr;
		}
	}

	void Exe(DBThread *t)
	{
		for (std::vector<RoleField *>::iterator itr = rold_list.begin(); itr != rold_list.end(); ++itr)
		{
			t->GetFieldManager()->Save(*itr);
		}
	}
	
	std::vector<RoleField *> rold_list;
};

#endif
