
#include "dbthread.h"

DBThread::~DBThread()
{

}

DBThread::DBThread(ThreadManager *thread_manager)
: BaseThread(thread_manager, ThreadManager::EXIT_NORMAL)
{
	m_name = "db";
	SetSleepTime(10);
}

bool DBThread::Init()
{
	return true;
}


bool DBThread::Run()
{
	return false;
}

void DBThread::RecvData(short type, ThreadID sid, int len, const char *data)
{

}


