
#include "basethread.h"
#include "lib/include/common/mutex.h"

void *Update(void * arg)
{
	BaseThread *gt = (BaseThread *)arg;
	gt->Update();
	return NULL;
}

BaseThread::BaseThread()
: m_thread(NULL)
, m_is_exit(false)
{

}

BaseThread::~BaseThread()
{
	delete m_thread;
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

