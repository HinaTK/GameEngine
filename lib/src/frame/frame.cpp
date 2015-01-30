
#include "frame/frame.h"
#include "libtimemanager.h"
#include "frame/netcommon.h"
#include "log/log.h"
#include "frame/message.h"

Frame::Frame()
: m_update_interval(200)
, m_ex_send_sleep_time(30)
, m_in_send_sleep_time(30)
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
	int		lastTime = GameTime::GetMilliSecond();	// 上一次更新时间
	int		curTime = 0;
	int		second = 0;
	int		oneMinute = 60000;

	m_log_thread.Create(WriteLog);
	this->Listen();
	while (1)
	{
		curTime = GameTime::GetMilliSecond();
		if (!recvQueue->IsEmpty())
		{
			msg = recvQueue->Val();
			if ((*msg) != NULL)
			{
				if ((*msg)->handle > 0)
				{
					this->Recv((*msg)->handle, (*msg)->data.mem, (*msg)->length);
				}
				delete (*msg);
			}
		}
		else
		{
			second = curTime < lastTime ? oneMinute : 0;
			int interval = (curTime + second) - lastTime;
			if (interval < m_update_interval)
			{
				GameTime::GameSleep(m_in_send_sleep_time < m_update_interval - interval ? m_in_send_sleep_time : m_update_interval - interval);
			}
			curTime = (lastTime + m_update_interval) % oneMinute;
		}

		second = curTime < lastTime ? oneMinute : 0;
		if ((curTime + second) - lastTime >= m_update_interval)
		{
			//timeNow = GameTime::Instance().Time();
			Update(GameTime::Time());
			lastTime = curTime;
		}
	}
	return true;
}




