#ifndef AOI_H
#define AOI_H

#include "GuiMi/define.h"
#include "common/commonvariable.h"

class AOI
{
public:
	AOI():
	obj_id(INVALID_OBJ_ID)
	{};
	AOI(ObjID obj_id, const Posi &center, Posi enter_radius, Posi leave_radius);


	bool IsIn(const Posi &pos);

	bool IsOut(const Posi &pos);

	ObjID obj_id;
	bool is_circle;
	Posi centre;
	Posi enter_radius;
	Posi leave_radius;
};

#endif // AOI_H
