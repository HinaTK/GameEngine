
#include "threadmanager.h"
#include "basethread.h"
#include "threadclass.h"
#include "rpc.h"
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
			Function::Info("Init %s thread error", (*itr)->GetName());
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

bool ThreadManager::SendMsg(ThreadID did, ThreadMsg &msg)
{
	if (m_thread.Exist(did))
	{
		m_thread[did]->PushMsg(msg);
		return true;
	}
	Function::Error("no this thread id %d from %d", did, msg.id);
	return false;
}

void ThreadManager::SendMsg(ThreadID did, TPT type, int len, const char *data, ThreadID sid)
{
	SendMsg(did, ThreadMsg(sid, type, len, data, m_thread[did]->GetMemory()));
}

void ThreadManager::SendMsg(ThreadID did, TPT type, char *obj)
{
	if (!SendMsg(did, ThreadMsg(type, obj)))
	{
		delete obj;
	}
}

void ThreadManager::SendMsg(ThreadID did, ThreadClass *tc)
{
	if (!SendMsg(did, ThreadMsg(ThreadSysID::TSID_CLASS, (char *)tc)))
	{
		delete tc;
	}
}

void ThreadManager::SendMsg(ThreadID did, TPT type, long long data, ThreadID sid)
{
	ThreadMsg tm;
	tm.id = sid;
	tm.type = type;
	*(long long *)&tm.data = data;
	SendMsg(did, tm);
}

void ThreadManager::RPC(ThreadID did, ThreadRPC *rpc)
{
	if (!SendMsg(did, ThreadMsg(ThreadSysID::TSID_RPC, (char *)rpc)))
	{
		delete rpc;
	}
}

char * ThreadManager::CreateData(ThreadID did, int len)
{
	if (m_thread.Exist(did))
	{
		return m_thread[did]->GetMemory()->Alloc(len);
	}
	return NULL;
}

void ThreadManager::CMD(TPT type, ThreadID sid, int len, const char *data, ThreadID did /*= -1*/)
{
	if (did != INVALID_THREAD_ID)
	{
		if (m_thread.Exist(did))
		{
			m_thread[did]->PushMsg(ThreadMsg(sid, type, len, data, m_thread[did]->GetMemory()));
		}
	}
	else
	{
		for (game::Array<BaseThread * >::iterator itr = m_thread.Begin(); itr != m_thread.End(); ++itr)
		{
			(*itr)->PushMsg(ThreadMsg(sid, type, len, data, m_thread[did]->GetMemory()));
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


