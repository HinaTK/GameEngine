
#include "center.h"
#include "net/netthread.h"
#include "db/dbthread.h"
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
	m_thread_manager.Register(new DBThread());
	return true;
}

void Center::Start()
{
	m_thread_manager.Start();
	while (IsRun())
	{
		char cmd_buf[512] = { 0 };
		gets(cmd_buf);
		if (strcmp(cmd_buf, "") == 0)
		{
		}
		else if (strcmp(cmd_buf, "create") == 0)
		{

		}
		else if (strcmp(cmd_buf, "exit") == 0)
		{
			SetExit();
		}
		else if (strcmp(cmd_buf, "login") == 0)
		{
			printf("do login\n");
		}
	}
}

void Center::Exit()
{

}

void Center::Wait()
{

}

