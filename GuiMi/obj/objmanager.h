
#ifndef OBJ_MANAGER_H
#define OBJ_MANAGER_H

#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"
#include "define.h"

/*
	场景的对象管理
*/

class Obj;
class ObjManager
{
public:
	ObjManager():m_obj_list(128)
	{

	}
	~ObjManager(){};
	int		Add(Obj *obj);
	Obj *	GetObj(ObjID obj_id);

private:
	game::Array<Obj *> m_obj_list;
};
#endif
