
#include "mainthread.h"
#include "lib/include/thread/threadmanager.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/baselistener.h"

MainThread::MainThread(ThreadManager *manager)
: BaseThread(manager)
{

}

int mm = 0;
void MainThread::Run()
{
	ThreadMsg *msg;
	do
	{
		bool is_sleep = true;
		while (m_recv_queue.Pop(msg/*, mm*/))
		{
			
			int ret = *(int *)msg->data;
			if (mm != ret)
			{
				printf("MainThread ... %d \n", ret);
			}
            else if (mm >= 100000)
			{
                m_is_exit = true;
				break;
			}
			
			//m_manager->SendMsg(ThreadManager::ID_DB, msg);
			//Send(ThreadManager::ID_DB, msg);
			is_sleep = false;
			++mm;
		}

		if (is_sleep)
		{
			GameTime::Sleep(2);
		}
		
	} while (!m_is_exit);
	printf("end \n");
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

