
#ifndef ROLE_FIELD_H
#define ROLE_FIELD_H

#include <vector>
#include "field.h"
#include "common/serverdef.h"

class RoleField
{
public:
	~RoleField()
	{
		for (std::vector<Field *>::iterator itr = fields.begin(); itr != fields.end(); ++itr)
		{
			delete *itr;
		}
	}
	RoleID	rid;
	std::vector<Field *> fields;
};


#endif