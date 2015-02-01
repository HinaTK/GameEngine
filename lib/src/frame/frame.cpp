
#include "frame/frame.h"
#include "libtimemanager.h"
#include "frame/netcommon.h"
#include "log/log.h"
#include "frame/message.h"

Frame::Frame()
: m_update_interval(200)
// , m_ex_send_sleep_time(30)
// , m_in_send_sleep_time(30)
{
	
}

void *Listen(void * arg)
{
	Frame *frame = (Frame *)arg;
	if (frame == NULL)
	{
		return NULL;
	}
	
	frame->GetNetManager()->Listen();
	return NULL;
}


void *WriteLog(void * arg)
{
	static const unsigned int sleepTime = 60 * 1000;
	while (true)
	{
		//Log::Instance().Flush();
		GameTime::GameSleep(sleepTime);
	}
	return NULL;
}

void Frame::Listen()
{
	m_listen_thread.Create(::Listen, this);
}


void Frame::Send( NetHandle handle, const char *buf, unsigned int length )
{
	m_net_manager.Send(handle, buf, length);
}

bool Frame::Run()
{
	GameMsg		**msg = NULL;
	MsgQueue	*recvQueue = m_net_manager.GetMsgQueue();
	unsigned long long		last_time = GameTime::MilliSecond();	// 上一次更新时间
	unsigned long long		cur_time = 0;
	unsigned long long		second = 0;
	unsigned long long		oneMinute = 60000;

	m_log_thread.Create(WriteLog);
	this->Listen();
	while (1)
	{
		cur_time = GameTime::MilliSecond();
		if (!recvQueue->IsEmpty())
		{
			msg = recvQueue->Val();
			if ((*msg) != NULL)
			{
				if ((int)(*msg)->handle >= (int)0)
				{
					this->Recv((*msg)->handle, (*msg)->data.mem, (*msg)->length);
				}
				delete (*msg);
			}
		}
		else
		{
			unsigned long long interval = cur_time - last_time - 1;
			if (interval < m_update_interval)
			{
				GameTime::GameSleep((unsigned int)(m_update_interval - interval));
			}
		}

		if ((cur_time - last_time) >= m_update_interval)
		{
			Update(GameTime::Time());
			last_time = cur_time;
		}
	}
	return true;
}




