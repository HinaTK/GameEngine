
#include "threadmanager.h"
#include "basethread.h"

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

int ThreadManager::Register(BaseThread *bt, char exit)
{
	ThreadID id = m_thread.Insert(bt);
	bt->SetID(id);
	m_exit[exit].push_back(id);
	return id;
}

bool ThreadManager::Init()
{
	for (game::Array<BaseThread *>::iterator itr = m_thread.Begin(); itr != m_thread.End(); ++itr)
	{
		if (!(*itr)->Init())
		{
			printf("init thread %s error\n", (*itr)->GetName());
			return false;
		}
	}
	return true;
}

bool ThreadManager::Ready()
{
	for (game::Array<BaseThread *>::iterator itr = m_thread.Begin(); itr != m_thread.End(); ++itr)
	{
		if (!(*itr)->Ready())
		{
			printf("ready thread %s error\n", (*itr)->GetName());
			return false;
		}
	}
	return true;
}

void ThreadManager::Start()
{
	for (game::Array<BaseThread *>::iterator itr = m_thread.Begin(); itr != m_thread.End(); ++itr)
	{
		(*itr)->Start();
	}
}

void ThreadManager::SendMsg(short type, ThreadID did, int len, const char *data, ThreadID sid)
{
	m_thread[did]->PushMsg(new ThreadMsg(type, sid, len, data));
}

void ThreadManager::CMD(short type, ThreadID sid, int len, const char *data, ThreadID did /*= -1*/)
{
	if (did != INVALID_THREAD_ID)
	{
		if (m_thread.Exist(did))
		{
			m_thread[did]->PushMsg(new ThreadMsg(type, sid, len, data));
		}
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
	CMD(ThreadSysID::TSID_EXIT, INVALID_THREAD_ID, 0, NULL);
}

void ThreadManager::Wait()
{
	for (int i = EXIT_NORMAL; i < EXIT_MAX; ++i)
	{
		for (std::vector<int>::iterator itr = m_exit[i].begin(); itr != m_exit[i].end(); ++itr)
		{
			m_thread[*itr]->Wait();
		}
	}
}


