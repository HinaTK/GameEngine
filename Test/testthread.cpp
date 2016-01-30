
#include "testthread.h"

TestThread2::TestThread2(ThreadManager *manager)
: BaseThread(manager)
{

}

TestThread2::~TestThread2()
{

}

int tt2 = 0;
void TestThread2::Run()
{
	ThreadMsg *msg;
	do
	{
		bool is_sleep = true;
		while (m_recv_queue.Pop(msg))
		{

			int ret = *(int *)msg->data;
			if (tt2 != ret)
			{
				printf("MainThread ... %d \n", ret);
			}
			else if (tt2 >= 1000000)
			{
				m_is_exit = true;
				break;
			}
			delete msg;
			//m_manager->SendMsg(ThreadManager::ID_DB, msg);
			//Send(ThreadManager::ID_DB, msg);
			is_sleep = false;
			++tt2;
		}

		if (is_sleep)
		{
			GameTime::Sleep(2);
		}

	} while (!m_is_exit);
	printf("end \n");
}

void TestThread2::Init()
{

}

