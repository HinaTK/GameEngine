
#include "global.h"
#include "main/center.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/socketthread.h"
#include "lib/include/inner/inneraccepter.h"
#include "lib/include/gate/gateaccepter.h"


Global::Global(ThreadManager *manager)
: BaseThread(manager)
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

void Global::Ready()
{
	
}

bool Global::Run()
{
	return false;
}

void Global::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	
}
