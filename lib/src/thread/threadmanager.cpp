
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
: m_is_exit(false)
{
	for (int i = 0; i < ID_MAX; ++i)
	{
		m_thread[i] = NULL;
	}
}

void ThreadManager::Register(unsigned char id, BaseThread *bt)
{
	m_thread[id] = bt;
}

void ThreadManager::Start()
{
	for (int i = 0; i < ID_MAX; ++i)
	{
		m_thread[i]->Start();
	}
}

void ThreadManager::SendMsg(unsigned char id, ThreadMsg *msg)
{
	if (id < ThreadManager::ID_MAX)
	{
		m_thread[id]->PushMsg(msg);
	}
	else
	{
		// ��ӡ��ջ
	}
}

void ThreadManager::Exit()
{
	for (int i = 0; i < ID_MAX; ++i)
	{
		if (m_thread[i])
		{
			m_thread[i]->Exit();
		}
	}
}

void ThreadManager::Wait()
{
	for (int i = 0; i < ID_MAX; ++i)
	{
		if (m_thread[i])
		{
			m_thread[i]->Wait();
		}
	}
	
	// ת���̱߳����������߳��˳�������˳�����Ȼ��Ӱ���̼߳�ͨ��
	m_is_exit = true;
}


