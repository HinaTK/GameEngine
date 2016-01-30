
#include "basethread.h"
#include "lib/include/common/mutex.h"

void *Update(void * arg)
{
	((BaseThread *)arg)->Run();
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
	m_thread = new std::thread(::Update, this);
}

void BaseThread::PushMsg(ThreadMsg *msg)
{
	m_recv_queue.Push(msg);
}

void BaseThread::Wait()
{
	if (m_thread)
	{
		m_thread->join();
	}
}



