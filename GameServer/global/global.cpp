
#include "global.h"
#include "scene/obj/role.h"
#include "lib/include/gate/proto.h"

Global::Global(ThreadManager *thread_manager)
: BaseThread(thread_manager)
{
	m_name = "global";
}

Global::~Global()
{

}

bool Global::Init()
{
	return true;
}

bool Global::Run()
{
	return false;
}

void Global::RecvData(TPT type, ThreadID sid, int len, const char *data)
{

}
