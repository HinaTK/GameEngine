#ifndef OBSERVER_H
#define OBSERVER_H

#include "define.h"
#include "obj/obj.h"

class Observer
{
public:
	Observer():
	obj_id(Obj::INVALID_OBJ_ID), 
	pos(0, 0),
	be_observe_area_pos(-2,-2), 
	be_observer_index(-1)
	{

	};
	~Observer(){};

	ObjID	obj_id;
	Posi	pos;			// ����λ��

	Posi			be_observe_area_pos;	// ���۲�����
	unsigned int	be_observer_index;	// ���ڱ��۲����������

	void *	operator new(size_t c);
	void	operator delete(void *m);

private:
};

#endif // OBSERVER_H
