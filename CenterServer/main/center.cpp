
#include "center.h"
#include "net/netthread.h"
#include "net/callback.h"
#include "db/dbthread.h"
#include "net/src/proto.h"


Center::Center()
{

}

Center::~Center()

{

}

bool Center::Init()
{
	m_thread_manager.Register(new NetThread(&m_thread_manager));
	db_thread_id[0] = m_thread_manager.Register(new DBThread(&m_thread_manager), ThreadManager::EXIT_FINALLY);
	db_thread_id[1] = m_thread_manager.Register(new DBThread(&m_thread_manager), ThreadManager::EXIT_FINALLY);
	return m_thread_manager.Init();
}

void Center::Start()
{
	m_thread_manager.Ready();
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

