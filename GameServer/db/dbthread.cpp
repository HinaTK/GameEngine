
#include "dbthread.h"
#include "lib/include/thread/threadmanager.h"


DBThread::~DBThread()
{

}

DBThread::DBThread(ThreadManager *manager)
: BaseThread(manager, NULL, ThreadManager::EXIT_NORMAL)
{

}

void DBThread::Init()
{

}

int dbi = 0;
bool DBThread::Run()
{
	return false;
}

void DBThread::RecvData(short type, int sid, int len, const char *data)
{

}


