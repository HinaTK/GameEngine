
#include "basethread.h"
#include "threadmanager.h"
#include "lib/include/common/mutex.h"
#include "lib/include/base/interface.h"

void *Update(void * arg)
{
	((BaseThread *)arg)->Loop();
	return NULL;
}

BaseThread::BaseThread(ThreadManager *manager, void *arg, char exit)
: m_id(-1)
, m_manager(manager)
, m_arg(arg)
, m_thread(NULL)
, m_is_exit(false)
, m_is_start(false)
, m_sleep_time(2)
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
	if (!m_is_start)
	{
		Init(m_arg);
		m_thread = new std::thread(::Update, this);
		m_is_start = true;
	}
}

void BaseThread::Loop(bool sleep)
{
    ThreadMsg *msg;
    bool is_sleep = sleep;
    do
    {
        is_sleep = sleep;
        while (m_recv_queue.Pop(msg)/* && msg != NULL*/)
        {
            if (msg->type > ThreadSysID::MAX_ID)
            {
                this->RecvData(msg->type, msg->id, msg->length, msg->data);
            }
            else if (msg->type == ThreadSysID::TSID_EXIT)
            {
                this->Exit();
            }
			
            delete msg;
            is_sleep = false;
        }
        if (!this->Run() && is_sleep)
        {
            Time::Sleep(m_sleep_time);
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
	Loop(false);
}




