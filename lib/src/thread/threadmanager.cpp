
#include "threadmanager.h"
#include "lib/include/timemanager/gametime.h"

ThreadManager::~ThreadManager()
{
	for (int i = 0; i < ID_MAX; ++i)
	{
		if (m_thread[i])
		{
			delete m_thread[i];
		}
	}
}

ThreadManager::ThreadManager()
{
	for (int i = 0; i < ID_MAX; ++i)
	{
		m_thread[i] = NULL;
	}
}

void ThreadManager::Register(unsigned char id, BaseThread *bt, unsigned int exit /*= EXIT_NORMAL*/)
{
	m_thread[id] = bt;
	m_exit[exit].push_back(id);
}

void ThreadManager::Start()
{
	for (int i = 0; i < ID_MAX; ++i)
	{
		if (m_thread[i])
		{
			m_thread[i]->Start();
		}
	}
}

void ThreadManager::SendMsg(unsigned char id, ThreadMsg *msg)
{
	m_thread[id]->PushMsg(msg);
}

void ThreadManager::Exit()
{
	for (std::vector<unsigned char>::iterator itr = m_exit[EXIT_NORMAL].begin(); itr != m_exit[EXIT_NORMAL].end(); ++itr)
	{
		m_thread[*itr]->Exit();
	}
}

void ThreadManager::Wait()
{
	for (std::vector<unsigned char>::iterator itr = m_exit[EXIT_NORMAL].begin(); itr != m_exit[EXIT_NORMAL].end(); ++itr)
	{
		m_thread[*itr]->Wait();
	}

	for (int i = EXIT_NORMAL + 1; i < EXIT_MAX; ++i)
	{
		for (std::vector<unsigned char>::iterator itr = m_exit[i].begin(); itr != m_exit[i].end(); ++itr)
		{
			m_thread[*itr]->Exit();
			m_thread[*itr]->Wait();
		}
	}
}


