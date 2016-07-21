
#include "dbthread.h"
#include "message/threadproto.h"

DBThread::~DBThread()
{

}

DBThread::DBThread(ThreadManager *manager)
: BaseThread(manager, NULL, ThreadManager::EXIT_NORMAL)
{

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
	switch (type)
	{
	case ThreadProto::TP_LOAD_ROLE:
		printf("load role ...\n");
	default:
		break;
	}
}


