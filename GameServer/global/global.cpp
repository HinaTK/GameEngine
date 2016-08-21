
#include "global.h"

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

void Global::RecvData(short type, ThreadID sid, int len, const char *data)
{

}
