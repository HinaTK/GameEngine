
#ifndef GATE_ROLE_QUEUE_H
#define GATE_ROLE_QUEUE_H

#include "lib/include/thread/rpc.h"
#include "lib/include/thread/threadclass.h"
#include "lib/include/gate/gatethread.h"

class GateRegRoleRet : public ThreadClass
{
public:
	void Exe(BaseThread *t){
		// todo in the scene thread,find the role,and set the queue
	}
	unsigned int index;
};

class GateRegRole : public ThreadRPC
{
public:
	ThreadClass * Call(BaseThread *t)
	{
		GateRegRoleRet *ret = new GateRegRoleRet();
		ret->index = ((GateThread*)t)->RegRole(queue);
		return ret;
	}
	
	MsgQueue<NetMsg> *queue;
};



class GateDelRole : public ThreadClass
{
public:
	void Exe(BaseThread *t){((GateThread*)t)->DelRole(index);}
	unsigned int index;
};

#endif