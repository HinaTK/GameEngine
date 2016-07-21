
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
	this->Run();
}


void Center::Cmd(char *buf)
{
	if (strcmp(buf, "create") == 0)
	{

	}
	else if (strcmp(buf, "login") == 0)
	{
		printf("do login\n");
	}
}

void Center::Exit()
{

}

void Center::Wait()
{

}

