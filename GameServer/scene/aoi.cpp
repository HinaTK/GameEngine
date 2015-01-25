#include "aoi.h"


AOI::AOI(ObjID obj_id, const Posi &_center, Posi _enter_radius, Posi _leave_radius)
{
}

bool AOI::IsIn(const Posi &pos)
{
	if (is_circle)
	{
		Posi delta_pos = pos - centre;
		return (delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y) < (enter_radius.x * enter_radius.x);
	}
	else
	{
		if (pos.x >= centre.x - enter_radius.x && pos.x < centre.x + enter_radius.x
			&& pos.y >= centre.y - enter_radius.y && pos.y < centre.y + enter_radius.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

bool AOI::IsOut(const Posi &pos)
{
	if (is_circle)
	{
		Posi delta_pos = pos - centre;
		return (delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y) >= (enter_radius.x * enter_radius.x);
	}
	else
	{
		if (pos.x < centre.x - leave_radius.x || pos.x >= centre.x + leave_radius.x
			|| pos.y < centre.y - leave_radius.y || pos.y >= centre.y + leave_radius.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}