
#include "rpc.h"
#include "basethread.h"
#include "threadsysid"

void ThreadRPC::Exe(BaseThread *t, ThreadID id)
{
	Call(t);
	t->GetManager()->SendMsg(id, Ret());
}