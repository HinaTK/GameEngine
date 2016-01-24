
#include "dbthread.h"


DBThread::~DBThread()
{

}

DBThread::DBThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void DBThread::Init()
{

}

void DBThread::Run()
{
	ThreadMsg *msg;
	do 
	{
		while (m_recv_queue.Pop(msg))
		{
			printf("DBThread %d ...\n", *(int *)msg->data);
			delete msg;
		}
		
		GameTime::Sleep(100);
	} while (!m_is_exit);
}


