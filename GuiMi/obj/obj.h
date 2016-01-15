#ifndef OBJ_H
#define OBJ_H

#include "define.h"
#include "common/commonvariable.h"

class Obj
{
public:
	Obj(): 
	m_obj_id(0),
	m_obj_pos(0,0)
	{

	}
	~Obj(){};

	static const int INVALID_OBJ_ID = -1;
	/*
		其它的对象进入自己的AOI（感兴趣区域）
	*/

	void				OnEnterAOI(ObjID obj_id);

	void				OnLeaveAOI(ObjID obj_id);

	ObjID				GetObjID(){return m_obj_id;}

	const Posi &		GetPos()const{return m_obj_pos;}

	void				SetPos(const Posi &p);

protected:
	ObjID	m_obj_id;
	Posi	m_obj_pos;
private:
	
};

#endif
