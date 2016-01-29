
#include "obj.h"
#include "scene/scene.h"


Obj::Obj(int type)
: m_obj_type(type)
, m_obj_id(0)
, m_obj_pos(0, 0)
, m_scene(NULL)
{

}

void Obj::OnEnterAOI( ObjID obj_id )
{

}

void Obj::OnLeaveAOI( ObjID obj_id )
{

}

void Obj::SetPos( const Posi &p )
{
	m_obj_pos.x = p.x;
	m_obj_pos.y = p.y;
}



