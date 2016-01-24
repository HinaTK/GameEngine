
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

	if (m_forward_thread)
	{
		delete m_forward_thread;
	}
}

ThreadManager::ThreadManager()
: m_forward_thread(NULL)
, m_is_exit(false)
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

void *ThreadFun(void * arg)
{
	ThreadManager *manager = (ThreadManager *)arg;
	while (manager->IsRun())
	{
		manager->Update();
	}
	return NULL;
}

void ThreadManager::Start()
{
	m_forward_thread = new std::thread(::ThreadFun, this);
	for (int i = 0; i < ID_MAX; ++i)
	{
		m_thread[i]->Start();
	}
}

void ThreadManager::Update()
{
	bool is_sleep = true;
	GlobalMsg *msg = NULL;
	for (int i = 0; i < ID_MAX; ++i)
	{
		while (m_thread[i]->PopMsg(msg) && msg != NULL)
		{
			m_thread[msg->type]->PushMsg(msg->msg);
			delete msg;
			is_sleep = false;
			printf("ffffffffffffffffffffffffffff\n");
		}
	}

	if (is_sleep)
	{
		GameTime::Sleep(10);
	}
}

void ThreadManager::PushMsg(unsigned char id, ThreadMsg *msg)
{
	if (id < ThreadManager::ID_MAX)
	{
		m_thread[id]->PushMsg(msg);
	}
	else
	{
		// 打印堆栈
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
	
	// 转发线程必须在其他线程退出后才能退出，不然会影响线程间通信
	m_is_exit = true;
	if (m_forward_thread)
	{
		m_forward_thread->join();
	}
}


