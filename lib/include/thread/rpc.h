
#ifndef THREAD_RPC_H
#define THREAD_RPC_H

#include "common/serverdef.h"

class BaseThread;
class ThreadClass;
class ThreadRPC
{
public:

	virtual ThreadClass * Call(BaseThread *t){ return 0; }

	void Exe(BaseThread *t, ThreadID id);

};



#endif