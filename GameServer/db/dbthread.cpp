
#include "dbthread.h"
#include "lib/include/thread/threadmanager.h"


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
	
}

void DBThread::RecvMsg(ThreadMsg *msg)
{
	struct qqq
	{
		int id;
		int val;
	};

	for (int i = 0; i < 1000001; ++i)
	{
		qqq q{ ThreadManager::ID_DB, i };
		ThreadMsg *msg = new ThreadMsg(sizeof(qqq), (const char *)&q);
		m_manager->SendMsg(ThreadManager::ID_MAIN, msg);
		// 				ThreadMsg *msg2 = new ThreadMsg(sizeof(int), (const char *)&i);
		// 				m_thread_manager.PushMsg(ThreadManager::ID_DB, msg2);
	}
}


