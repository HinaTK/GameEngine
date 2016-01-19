
#include <signal.h>
#include <thread>
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
		m_net_manager.Exit();
		Exit();
		Wait();
	}
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
	Frame *frame = (Frame *)arg;
	while (frame->IsRun())
	{
		frame->GetLogManager()->Flush();
		GameTime::Sleep(1000);
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
	unsigned long long		last_time_ms = GameTime::Instance().FrameTime();	// 上一次更新时间
	unsigned long long		cur_time_ms = 0;
	unsigned long long		second = 0;
	unsigned long long		oneMinute = 60000;

	std::thread log_thread(::WriteLog, this);
	std::thread listen_thread(::Listen, this);
	while (m_is_run)
	{
		// update 机制需要修改
		GameTime::Instance().Update();
		m_net_manager.Update();
		
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

	log_thread.join();
	listen_thread.join();

	return true;
}




