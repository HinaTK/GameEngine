
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

void ThreadManager::SendMsg(unsigned char sid, unsigned char did, int len, const char *data)
{
	m_thread[did]->PushMsg(new ThreadMsg(CMD_NOT, sid, len, data));
}

void ThreadManager::CMD(unsigned char type, unsigned char sid, int len, const char *data, unsigned char did /*= -1*/)
{
	if (did != (unsigned char)-1)
	{
		m_thread[did]->PushMsg(new ThreadMsg(type, sid, len, data));
	}
	else
	{
		for (int i = 0; i < ID_MAX; ++i)
		{
			if (m_thread[i]) m_thread[i]->PushMsg(new ThreadMsg(type, sid, len, data));
		}
	}
}

void ThreadManager::Exit()
{
	CMD(CMD_EXIT, -1, 0, NULL);
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
			m_thread[*itr]->Wait();
		}
	}
}


