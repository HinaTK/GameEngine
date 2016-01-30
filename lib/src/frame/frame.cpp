
#include <signal.h>
#include "frame.h"
#include "netcommon.h"
#include "message.h"
#include "msgcallback.h"
#include "log/log.h"
#include "lib/include/common/mutex.h"
#include "lib/include/timemanager/gametime.h"
#include "lib/include/common/memoryvl.h"


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
: m_sleep_time_ms(2)
, m_is_run(true)
{
	SignalCatch::g_frame = this;
	signal(SIGINT, SignalCatch::Catch);
#ifdef __unix
	signal(SIGPIPE, SIG_IGN); // socket send if close
#endif
    
}

Frame::~Frame()
{
	SetExit();
}

bool Frame::Init()
{
	return true;
}

void Frame::SetFPS(int ms)
{
	GameTime::Instance().SetFPS(ms);
}

void Frame::SetExit()
{
	if (m_is_run)
	{
		m_is_run = false;
		Exit();
		Wait();
	}
}

void Frame::UpdateAll(unsigned long long interval)
{
	m_time_event_manager.Update();
	Update((unsigned int)interval, GameTime::Instance().Time());
}


void Frame::Loop()
{

}

bool Frame::Run()
{
	unsigned long long		last_time_ms = GameTime::Instance().FrameTime();	// 上一次更新时间
	unsigned long long		cur_time_ms = 0;
	unsigned long long		second = 0;
	unsigned long long		oneMinute = 60000;

	while (m_is_run)
	{
		Loop();
		// update 机制需要修改
		GameTime::Instance().Update();
		
		cur_time_ms = GameTime::Instance().FrameTime();
		if (cur_time_ms != last_time_ms)
		{
			UpdateAll(cur_time_ms - last_time_ms);
			last_time_ms = cur_time_ms;
		}
		else
		{
            GameTime::Sleep(m_sleep_time_ms);
		}
		
	}

	return true;
}




