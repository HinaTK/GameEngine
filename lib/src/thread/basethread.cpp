
#include "basethread.h"
#include "lib/include/common/mutex.h"

void *Update(void * arg)
{
	((BaseThread *)arg)->Loop();
	return NULL;
}

BaseThread::BaseThread(ThreadManager *manager)
: m_manager(manager)
, m_thread(NULL)
, m_is_exit(false)
{

}

BaseThread::~BaseThread()
{
	if (m_thread)
	{
		delete m_thread;
	}
}

void BaseThread::Start()
{
	Init();
	m_thread = new std::thread(::Update, this);
}

void BaseThread::Loop()
{
	ThreadMsg *msg;
	do 
	{
		Run();
		while (m_recv_queue.Pop(msg))
		{
			this->RecvMsg(msg);
			delete msg;
		}

	} while (!m_is_exit);
}

void BaseThread::PushMsg(ThreadMsg *msg)
{
	m_recv_queue.Push(msg);
}

void BaseThread::Exit()
{
	m_is_exit = true;
}

void BaseThread::Wait()
{
	if (m_thread)
	{
		m_thread->join();
	}
	Loop();
}




