
#include "gateway.h"
#include "net/netthread.h"
#include "lib/include/common/serverconfig.h"


Gateway::Gateway()
{

}

Gateway::~Gateway()
{

}

bool Gateway::Init()
{
	GatawayConfig::Instance().Init(); 
	for (unsigned int i = 0; i < GatawayConfig::Instance().m_server.size(); ++i)
	{
		NetThread *nt = new NetThread((&m_thread_manager), new int(i));
	}
	
	return true;
}

void Gateway::Start()
{
	m_thread_manager.Start();
	
	while (IsRun())
	{
		char cmd_buf[512] = { 0 };
		gets(cmd_buf);
		if (strncmp(cmd_buf, "exit", 4) == 0)
		{
			SetExit();
		}
	}
}

void Gateway::Exit()
{

}

void Gateway::Wait()
{

}

