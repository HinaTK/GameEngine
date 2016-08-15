﻿
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

void BaseThread::Loop(bool sleep)
{
	ThreadMsg msg;
    bool is_sleep = sleep;
    do
    {
        is_sleep = m_recv_queue.Size() > 0 ? false : sleep;
        
        while (m_recv_queue.Pop(msg)/* && msg != NULL*/)
        {
            if (msg.type > ThreadSysID::MAX_ID)
            {
                this->RecvData(msg.type, msg.id, msg.length, msg.data);
            }
            else
            {
				if (msg.type == ThreadSysID::TSID_EXIT)
				{
					this->Exit();
				}
				else
				{
					this->SysCmd(msg);
				}
            }
            m_msg_memory.Free(msg);
        }
        if (!this->Run() && is_sleep)
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
			printf("pong %d %s\n", m_id, m_name.c_str());
		}
		else 
		{
			if (!this->CMD(msg.type, msg.id, msg.length, msg.data))
			{
				printf("Thread %d no this cmd: %s\n", m_id, msg.data);
			}
		}
	}
}


