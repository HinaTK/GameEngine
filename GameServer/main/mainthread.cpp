
#include "mainthread.h"
#include "lib/include/thread/threadmanager.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/baselistener.h"

MainThread::MainThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void MainThread::Run()
{
	ThreadMsg *msg;
	do
	{
		bool is_sleep = true;
		while (m_recv_queue.Pop(msg))
		{
			int ret = *(int *)msg->data;
			printf("MainThread ... %d \n", ret);
			m_manager->SendMsg(ThreadManager::ID_DB, msg);
			//Send(ThreadManager::ID_DB, msg);
			is_sleep = false;
		}

		if (is_sleep)
		{
			GameTime::Sleep(10);
		}
		
	} while (!m_is_exit);
}

void MainThread::Init()
{
// 	int ret = m_net_manager.ConnectServer(
// 		ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].ip,
// 		ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].port,
// 		new BaseListener(&m_net_manager),
// 		&m_i_call_back);
// 
// 	if (ret == INVALID_NET_HANDLE)
// 	{
// 		printf("connect data server fail ...\n");
// 		return;
// 	}
// 
// 	m_net_manager.Listen();
}

