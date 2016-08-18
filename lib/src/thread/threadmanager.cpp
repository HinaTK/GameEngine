
#include "threadmanager.h"
#include "basethread.h"
#include "lib/include/base/function.h"

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
			Function::Info("Init thread %s error", (*itr)->GetName());
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
			Function::Info("Ready thread %s error", (*itr)->GetName());
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

void ThreadManager::SendMsg(ThreadID did, short type, int len, const char *data, ThreadID sid)
{
	m_thread[did]->PushMsg(ThreadMsg(type, sid, len, data, m_thread[did]->GetMemory()));
}

void ThreadManager::SendMsg(ThreadID did, ThreadMsg &msg)
{
	m_thread[did]->PushMsg(msg);
}

char * ThreadManager::CreateData(ThreadID did, int len)
{
	return m_thread[did]->GetMemory()->Alloc(len);
}

// void ThreadManager::SendMsg(ThreadID did, ThreadMsg &msg)
// {
// 	m_thread[did]->PushMsg(msg);
// }

void ThreadManager::CMD(short type, ThreadID sid, int len, const char *data, ThreadID did /*= -1*/)
{
	if (did != INVALID_THREAD_ID)
	{
		if (m_thread.Exist(did))
		{
			m_thread[did]->PushMsg(ThreadMsg(type, sid, len, data, m_thread[did]->GetMemory()));
		}
	}
	else
	{
		for (game::Array<BaseThread * >::iterator itr = m_thread.Begin(); itr != m_thread.End(); ++itr)
		{
			(*itr)->PushMsg(ThreadMsg(type, sid, len, data, m_thread[did]->GetMemory()));
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


