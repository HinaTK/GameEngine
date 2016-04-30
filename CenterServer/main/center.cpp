
#include "center.h"
#include "net/netthread.h"
#include "lib/include/common/serverconfig.h"


Center::Center()
{

}

Center::~Center()
{

}

bool Center::Init()
{
	CenterConfig::Instance().Init();
	m_thread_manager.Register(new NetThread(&m_thread_manager));
	return true;
}

void Center::Start()
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

void Center::Exit()
{

}

void Center::Wait()
{

}

