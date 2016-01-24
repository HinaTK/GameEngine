
#include "basethread.h"
#include "lib/include/common/mutex.h"

void *Update(void * arg)
{
	BaseThread *gt = (BaseThread *)arg;
	gt->Run();
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

bool BaseThread::PopMsg(GlobalMsg *msg)
{
	return m_send_queue.Pop(msg);
}

void BaseThread::Send(unsigned char id, ThreadMsg *msg)
{
	m_send_queue.Push(new GlobalMsg(id, msg));
}

void BaseThread::Wait()
{
	if (m_thread)
	{
		m_thread->join();
	}
}



