
#include "threadmanager.h"

ThreadManager::~ThreadManager()
{
	delete m_thread;
}

ThreadManager::ThreadManager()
{
	m_thread = new BaseThread[T_MAX];
}

void ThreadManager::Start()
{
	for (int i = 0; i < T_MAX; ++i)
	{
		m_thread[i].Start();
	}
}

