
#include <signal.h>
#include "frame/frame.h"

#include "frame/netcommon.h"
#include "log/log.h"
#include "frame/message.h"

namespace SignalCatch
{
	Frame *g_frame;
	void Catch(int sig)
	{
		if (g_frame != NULL)
		{
			g_frame->SetExit();
			signal(sig, SignalCatch::Catch);
		}
	}
}

Frame::Frame()
: m_update_interval(200)
, m_is_run(true)
{
	SignalCatch::g_frame = this;
	signal(SIGINT, SignalCatch::Catch);
}

Frame::~Frame()
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

void Frame::UpdateAll()
{
	m_time_manager.Update();
	Update(m_time_manager.Time());
}

bool Frame::Run()
{
	GameMsg		**msg = NULL;
	MsgQueue	*recvQueue = m_net_manager.GetMsgQueue();
	unsigned long long		last_time_ms = m_time_manager.MilliSecond();	// 上一次更新时间
	unsigned long long		cur_time_ms = 0;
	unsigned long long		second = 0;
	unsigned long long		oneMinute = 60000;

	m_log_thread.Create(WriteLog);
	this->Listen();
	while (m_is_run)
	{
		cur_time_ms = m_time_manager.MilliSecond();
		if (!recvQueue->IsEmpty())
		{
			msg = recvQueue->Pop();
			if ((*msg) != NULL)
			{
				if ((int)(*msg)->handle >= (int)0)
				{
					this->Recv(*msg);
				}
				// 内存交给下游处理
				// delete (*msg);
			}
		}
		else
		{
			unsigned long long interval = cur_time_ms - last_time_ms - 1;
			if (interval < m_update_interval)
			{
				GameTime::GameSleep((unsigned int)(m_update_interval - interval));
			}
		}

		if ((cur_time_ms - last_time_ms) >= m_update_interval)
		{
			UpdateAll();
			last_time_ms = cur_time_ms;
		}
	}
	m_net_manager.Exit();
	m_listen_thread.Join();
	Exit();
	return true;
}




