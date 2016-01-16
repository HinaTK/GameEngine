
#include "aoi.h"



AOI::AOI(ObjID _obj_id, const Posi &_center, Posi &_radius, bool _is_circle /*= false*/)
: obj_id(_obj_id)
, center(_center)
, radius(_radius)
, is_circle(_is_circle)
{

}


bool AOI::IsIn(const Posi &pos)
{
	if (is_circle)
	{
		Posi delta_pos = pos - center;
		return (delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y) < (radius.x * radius.x);
	}
	else
	{
		if (pos.x >= center.x - radius.x && pos.x < center.x + radius.x
			&& pos.y >= center.y - radius.y && pos.y < center.y + radius.y)
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
	return !IsIn(pos);
}