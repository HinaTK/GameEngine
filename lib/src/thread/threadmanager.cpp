
#include "threadmanager.h"
#include "lib/include/timemanager/gametime.h"

ThreadManager::~ThreadManager()
{
	for (game::Array<BaseThread * >::iterator itr = m_thread.Begin(); itr != m_thread.End(); ++itr)
	{
		if (*itr != NULL)
		{
			delete (*itr);
			*itr = NULL;
		}
	}
}

ThreadManager::ThreadManager()
{
	
}

int ThreadManager::Register(BaseThread *bt, void *arg, unsigned int exit /*= EXIT_NORMAL*/)
{
	unsigned int id = m_thread.Insert(bt);
	bt->SetID(id);
	bt->SetArg(arg);
	m_exit[exit].push_back(id);
	return id;
}

void ThreadManager::Start()
{
	for (game::Array<BaseThread * >::iterator itr = m_thread.Begin(); itr != m_thread.End(); ++itr)
	{
		(*itr)->Start();
	}
}

void ThreadManager::SendMsg(short type, unsigned char sid, unsigned char did, int len, const char *data)
{
	m_thread[did]->PushMsg(new ThreadMsg(type, sid, len, data));
}

void ThreadManager::SendMsg(short type, unsigned char did, int len, const char *data)
{
	m_thread[did]->PushMsg(new ThreadMsg(type, -1, len, data));
}

void ThreadManager::CMD(short type, int sid, int len, const char *data, int did /*= -1*/)
{
	if (did != -1)
	{
		m_thread[did]->PushMsg(new ThreadMsg(type, sid, len, data));
	}
	else
	{
		for (game::Array<BaseThread * >::iterator itr = m_thread.Begin(); itr != m_thread.End(); ++itr)
		{
			(*itr)->PushMsg(new ThreadMsg(type, sid, len, data));
		}
	}
}

void ThreadManager::Exit()
{
	CMD(ThreadSysID::TSID_EXIT, -1, 0, NULL);
}

void ThreadManager::Wait()
{
	for (std::vector<int>::iterator itr = m_exit[EXIT_NORMAL].begin(); itr != m_exit[EXIT_NORMAL].end(); ++itr)
	{
		m_thread[*itr]->Wait();
	}

	for (int i = EXIT_NORMAL + 1; i < EXIT_MAX; ++i)
	{
		for (std::vector<int>::iterator itr = m_exit[i].begin(); itr != m_exit[i].end(); ++itr)
		{
			m_thread[*itr]->Wait();
		}
	}
}


