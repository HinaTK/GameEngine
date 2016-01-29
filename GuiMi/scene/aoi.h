#ifndef AOI_H
#define AOI_H

#include "define.h"

class AOI
{
public:
	AOI():
	obj_id(INVALID_OBJ_ID){};
	AOI(ObjID _obj_id, const Posi &_center, Posi &_radius, bool _is_circle = false);


	bool IsIn(const Posi &pos);

	bool IsOut(const Posi &pos);

	ObjID obj_id;
	bool is_circle;
	Posi center;
	Posi radius;
};

#endif // AOI_H
