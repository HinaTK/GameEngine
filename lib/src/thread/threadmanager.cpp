
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
	delete m_write_thread;
	delete m_read_thread;
}

ThreadManager::ThreadManager()
: m_write_thread(new std::vector<BaseThread *>())
, m_read_thread(new std::vector<BaseThread *>())
{
	
}

int ThreadManager::Register(BaseThread *bt, char exit)
{
	m_write_thread->push_back(bt);
	ThreadID id = m_thread.Insert(bt);
	bt->SetID(id);
	m_exit[exit].push_back(id);
	return id;
}

void ThreadManager::Start()
{
	if (m_write_thread->size() > 0)
	{
		std::vector<BaseThread *> *temp = m_read_thread;
		m_read_thread = m_write_thread;
		m_write_thread = temp;
		m_write_thread->clear();
		for (std::vector<BaseThread *>::iterator itr = m_read_thread->begin(); itr != m_read_thread->end(); ++itr)
		{
			(*itr)->Start();
		}
		this->Start();
	}
}

void ThreadManager::SendMsg(short type, ThreadID did, int len, const char *data, ThreadID sid)
{
	m_thread[did]->PushMsg(new ThreadMsg(type, sid, len, data));
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


