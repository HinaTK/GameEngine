
#include "center.h"
#include "net/netthread.h"
#include "net/callback.h"
#include "db/dbthread.h"
#include "message/proto.h"
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
	db_thread_id[0] = m_thread_manager.Register(new DBThread(&m_thread_manager));
	db_thread_id[1] = m_thread_manager.Register(new DBThread(&m_thread_manager));
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
		ThreadManager thread_manager;
		NetManager net_manager(&thread_manager);
		NetHandle handle = net_manager.SyncConnect("127.0.0.1", 12348, new ClientCallBack());
		Proto::csLogin login;
		net_manager.Send(handle, sizeof(Proto::csLogin), (const char *)&login);

		printf("do login\n");
	}
}

void Center::Exit()
{

}

void Center::Wait()
{

}

