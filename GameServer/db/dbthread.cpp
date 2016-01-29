
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

int dbi = 0;
void DBThread::Run()
{
	ThreadMsg *msg;
	do 
	{
// 		while (m_recv_queue.Pop(msg, 0))
// 		{
// 			int ret = *(int *)msg->data;
// 			//if (dbi == ret)
// // 			{
// // 				printf("DBThread %d ...\n", ret);
// // 			}
// // 			dbi++;
// 			delete msg;
// 		}
		
		GameTime::Sleep(100);
	} while (!m_is_exit);
}


