
#include "dbthread.h"

DBThread::~DBThread()
{

}

DBThread::DBThread(ThreadManager *thread_manager)
: BaseThread(thread_manager, NULL, ThreadManager::EXIT_NORMAL)
{
	m_name = "db";
}

void DBThread::Init(void *arg)
{

}


bool DBThread::Run()
{
	return false;
}

void DBThread::RecvData(short type, ThreadID sid, int len, const char *data)
{

}


