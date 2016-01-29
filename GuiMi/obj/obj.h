
#ifndef OBJ_H
#define OBJ_H

#include "define.h"

class Scene;
class Obj
{
public:
	Obj(int type);
	virtual ~Obj(){};

	static const int INVALID_OBJ_ID = -1;
	enum
	{
		OBJ_ROLE,
	};
	/*
		其它的对象进入自己的AOI（感兴趣区域）
	*/

	void				OnEnterAOI(ObjID obj_id);
	void				OnLeaveAOI(ObjID obj_id);

	void				SetObjID(ObjID obj_id){ m_obj_id = obj_id; }
	ObjID				GetObjID(){return m_obj_id;}

	const Posi &		GetPos()const{return m_obj_pos;}
	void				SetPos(const Posi &p);

	Scene				*GetScene(){ return m_scene; }
	void				SetScene(Scene *scene){ m_scene = scene; }

protected:
	int		m_obj_type;
	ObjID	m_obj_id;
	Posi	m_obj_pos;
	Scene	*m_scene;
private:
	
};

#endif
