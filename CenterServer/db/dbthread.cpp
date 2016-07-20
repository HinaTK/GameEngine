
#include "dbthread.h"

DBThread::~DBThread()
{

}

DBThread::DBThread()
: BaseThread(NULL, ThreadManager::EXIT_NORMAL)
{

}

void DBThread::Init(void *arg)
{

}


bool DBThread::Run()
{
	return false;
}

void DBThread::RecvData(short type, int sid, int len, const char *data)
{

}


