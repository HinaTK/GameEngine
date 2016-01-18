
#include "dbthread.h"
#include "lib/include/timemanager/gametime.h"

DBThread::~DBThread()
{

}

DBThread::DBThread()
: BaseThread()
{

}

void DBThread::Update()
{
	int i = 0;
	ThreadMsg *msg;
	do 
	{
		while (m_msg_queue.Pop(msg))
		{
			printf("DBThread %d ...\n", *(int *)msg->data);
			delete []msg->data;
			delete msg;
		}
		
		GameTime::Sleep(100);
	} while (!m_is_exit);
	delete msg;
}


