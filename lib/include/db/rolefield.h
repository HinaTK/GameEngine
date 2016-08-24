
#ifndef ROLE_FIELD_H
#define ROLE_FIELD_H

#include <vector>
#include "common/serverdef.h"

class Field;
class RoleField
{
public:
	RoleID	rid;
	std::vector<Field *> fields;
};


#endif