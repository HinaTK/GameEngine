
#include <signal.h>
#include "frame/frame.h"
#include "frame/netcommon.h"
#include "frame/message.h"
#include "log/log.h"
#include "lib/include/timemanager/gametime.h"


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
	m_log_manager.SetGameTime(&GameTime::Instance());
}

Frame::~Frame()
{

}

void Frame::SetExit()
{
	m_is_run = false;
	m_net_manager.Exit();
	Exit();
	Wait();
	m_log_thread.Join();
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
	// 读取配置多少秒写log
	static const unsigned int sleepTime = 60 * 1000;
	Frame *frame = (Frame *)arg;
	while (frame->IsRun())
	{
		frame->GetLogManager()->Flush();
		GameTime::GameSleep(sleepTime);
	}
	frame->GetLogManager()->Flush();
	return NULL;
}

void Frame::Send( NetHandle handle, const char *buf, unsigned int length )
{
	m_net_manager.Send(handle, buf, length);
}

void Frame::UpdateAll(unsigned long long interval)
{
	m_time_event_manager.Update();
	Update((unsigned int)interval, GameTime::Instance().Time());
}

bool Frame::Run()
{
	GameMsg		**msg = NULL;
	MsgQueue	*recvQueue = m_net_manager.GetMsgQueue();
	unsigned long long		last_time_ms = GameTime::Instance().MilliSecond();	// 上一次更新时间
	unsigned long long		cur_time_ms = 0;
	unsigned long long		second = 0;
	unsigned long long		oneMinute = 60000;

	m_log_thread.Create(::WriteLog, this);
	m_listen_thread.Create(::Listen, this);
	while (m_is_run)
	{
		GameTime::Instance().Update();
		cur_time_ms = GameTime::Instance().MilliSecond();
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
			UpdateAll(cur_time_ms - last_time_ms);
			last_time_ms = cur_time_ms;
		}
	}
	m_net_manager.Exit();
	m_listen_thread.Join();
	Exit();
	return true;
}





