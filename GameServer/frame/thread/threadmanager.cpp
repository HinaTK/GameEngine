
#include "threadmanager.h"
#include "dbthread.h"

ThreadManager::~ThreadManager()
{
	for (int i = 0; i < T_MAX; ++i)
	{
		if (m_thread[i])
		{
			delete m_thread;
		}
	}
	delete[]m_thread;
}

ThreadManager::ThreadManager()
{
	m_thread = new BaseThread *[T_MAX];
	m_thread[T_DB] = new DBThread;
}

void ThreadManager::Start()
{
	for (int i = 0; i < T_MAX; ++i)
	{
		m_thread[i]->Start();
	}
}

void ThreadManager::PushMsg(unsigned int type, ThreadMsg *msg)
{
	m_thread[type]->PushMsg(msg);
}

