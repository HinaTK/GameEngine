
#include "basethread.h"
#include "lib/include/common/mutex.h"
#include "lib/include/timemanager/gametime.h"

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

}

// {
// 	do 
// 	{
// 		GameTime::Sleep(100);
// 	} while (!m_is_exit);
// }

void BaseThread::Start()
{
	m_thread = new std::thread(::Update, this);
}

void BaseThread::PushMsg(ThreadMsg *msg)
{
	m_msg_queue.Push(msg);
}

void BaseThread::Wait()
{
	if (m_thread)
	{
		m_thread->join();
	}
}

