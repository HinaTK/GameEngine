#include "objmanager.h"

int ObjManager::Add( Obj *obj )
{
	return m_obj_list.Push(obj);
}


Obj * ObjManager::GetObj( ObjID obj_id )
{
	if (obj_id >= m_obj_list.Size())
	{
		return NULL;
	}
	return m_obj_list[obj_id];
	//return m_obj_list[obj_id];
	//return m_obj_list + obj_id;
}

