
#include "objmanager.h"

int ObjManager::Add( Obj *obj )
{
	return m_obj_array.Insert(obj);
}


bool ObjManager::Del(ObjID obj_id)
{
	m_obj_array.Erase(obj_id);
	return true;
}

Obj * ObjManager::GetObj( ObjID obj_id )
{
	if (obj_id >= m_obj_array.Size())
	{
		return NULL;
	}
	return m_obj_array[obj_id];
}

