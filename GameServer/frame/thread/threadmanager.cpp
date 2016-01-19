
#include "threadmanager.h"
#include "dbthread.h"
#include "mainthread.h"

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
	m_thread[T_MAIN] = new MainThread;
}

void ThreadManager::Start()
{
	for (int i = 0; i < T_MAX; ++i)
	{
		m_thread[i]->Start();
	}
}

void ThreadManager::Update()
{
	GlobalMsg *msg;
	while (m_global_queue.Pop(msg))
	{
		if (msg->type < ThreadManager::T_MAX)
		{
			m_thread[msg->type]->PushMsg(msg->tm);
		}
		else
		{
			delete msg->tm;
		}
		
		delete msg;
	}
}

void ThreadManager::PushMsg(unsigned char type, ThreadMsg *msg)
{
	if (type < ThreadManager::T_MAX)
	{
		m_thread[type]->PushMsg(msg);
	}
	else
	{
		// ¥Ú”°∂—’ª
	}
	
}

void ThreadManager::PushGlobal(unsigned char type, ThreadMsg *msg)
{
	//m_global_queue.Push(msg);
}

void ThreadManager::Exit()
{
	for (int i = 0; i < T_MAX; ++i)
	{
		if (m_thread[i])
		{
			m_thread[i]->Exit();
		}
	}
}

void ThreadManager::Wait()
{
	for (int i = 0; i < T_MAX; ++i)
	{
		if (m_thread[i])
		{
			m_thread[i]->Wait();
		}
	}
}

