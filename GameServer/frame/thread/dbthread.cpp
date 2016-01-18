
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
	do 
	{
		printf("DBThread %d ...\n", ++i);
		GameTime::Sleep(100);
	} while (!m_is_exit);
}


