
#include "mainthread.h"
#include "threadmanager.h"

MainThread::MainThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void MainThread::Update()
{
	ThreadMsg *msg;
	do
	{
		while (m_recv_queue.Pop(msg))
		{
			printf("MainThread %d ...\n", *(int *)msg->data);
			GlobalMsg *gm = new GlobalMsg(ThreadManager::T_DB, msg);
			m_send_queue.Push(gm);
		}

		GameTime::Sleep(100);
	} while (!m_is_exit);
}

