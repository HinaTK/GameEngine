
#include "rpc.h"
#include "basethread.h"
#include "threadsysid.h"

void ThreadRPC::Exe(BaseThread *t, ThreadID id)
{
	t->GetManager()->SendMsg(id, Call(t));
}