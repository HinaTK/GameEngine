
#ifndef THREAD_RPC_H
#define THREAD_RPC_H

#include "common/serverdef.h"

class BaseThread;
class ThreadClass;
class ThreadRPC
{
public:

	virtual ThreadClass *Ret() = 0;

	virtual void Call(BaseThread *t){}

	void Exe(BaseThread *t, ThreadID id);

};



#endif