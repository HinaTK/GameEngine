#ifndef OBJMANAGER_H
#define OBJMANAGER_H

#include "global/globalvariable.h"
#include "common/commonvariable.h"
#include "common/datastructure/gamevector.h"


class Obj;
class ObjManager
{
public:
	ObjManager():m_obj_list(1024)
	{

	}
	~ObjManager(){};
	int		Add(Obj *obj);
	Obj *	GetObj(ObjID obj_id);

private:
	game::Vector<Obj *> m_obj_list;
};
#endif
