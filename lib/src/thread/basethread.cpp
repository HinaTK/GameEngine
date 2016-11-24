
#include "basethread.h"
#include "threadclass.h"
#include "lib/include/base/interface.h"
#include "lib/include/base/function.h"

void *Update(void * arg)
{
	((BaseThread *)arg)->Do();
	return NULL;
}

BaseThread::BaseThread(ThreadManager *manager, char exit)
: m_id(INVALID_THREAD_ID)
, m_name("")
, m_manager(manager)
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
		m_thread = new std::thread(::Update, this);
		m_is_start = true;
	}
}

void BaseThread::Do()
{
	Ready();
	Loop(true);
}

void BaseThread::Loop(bool sleep)
{
	ThreadMsg msg;
    bool is_sleep = sleep;
    do
    {
        is_sleep = m_recv_queue.Size() > 0 ? false : sleep;
        
        while (m_recv_queue.Pop(msg)/* && msg != NULL*/)
        {
            if (msg.type <= ThreadSysID::TSID_MAX_ID)
            {
				this->RecvData(msg.type, msg.id, msg.length, msg.data);
            }
            else
            {
            	switch(msg.type)
            	{
            	case ThreadSysID::TSID_CLASS:
            		if (msg.data != NULL) 
            		{
            			((ThreadClass *)msg.data)->Exe(this);
            			delete msg.data;
            		}		
            		continue;
            	case ThreadSysID::TSID_RPC:
            		if (msg.data != NULL) 
            		{
            			((ThreadRPC *)msg.data)->Exe(this, msg.id);
            			delete msg.data;
            		}
            		continue;	
            	case ThreadSysID::TSID_EXIT:
            		this->Exit();
            		break;
            	case ThreadSysID::TSID_THREAD_CMD:	
            		this->SysCmd(msg);
            		break;
				default:
					Function::Error("invalid thread sys id %d", msg.type);
            	}
            }
            m_msg_memory.Free(msg);
        }
        if (!Run() && is_sleep)
        {
            Time::Sleep(m_sleep_time);
        }

    } while (!m_is_exit);
}


void BaseThread::PushMsg(ThreadMsg &msg)
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

void BaseThread::SysCmd(ThreadMsg &msg)
{
	if (msg.length > 0)
	{
		if (strcmp(msg.data, "ping") == 0)
		{
			Function::CMD("pong %d %s", m_id, m_name.c_str());
		}
		else 
		{
			if (!this->CMD(msg.type, msg.id, msg.length, msg.data))
			{
				Function::CMD("Thread %d no this cmd: %s", m_id, msg.data);
			}
		}
	}
}


