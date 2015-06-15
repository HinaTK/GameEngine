
#include <signal.h>
#include <thread>
#include "frame.h"
#include "netcommon.h"
#include "message.h"
#include "log/log.h"
#include "lib/include/timemanager/gametime.h"
#include "lib/include/common/memoryvl.h"
#include "lib/include/common/commonconfig.h"
// #include "DLL/export.h"
// #include "DLL/dll.h"


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
: m_sleep_time_ms(1)
, m_is_run(true)
{
	SignalCatch::g_frame = this;
	signal(SIGINT, SignalCatch::Catch);
}

Frame::~Frame()
{

}

bool Frame::Init()
{
	MemoryVL::Instance().Init(CommonConfig::Instance().GetMemoryVLVector());
// 	DLL *dll;
// 	Register(&dll);
// 	dll->Show();
	return true;
}

void Frame::SetFPS(int ms)
{
	GameTime::Instance().SetFPS(ms);
}

void Frame::SetExit()
{
	m_is_run = false;
	m_net_manager.Exit();
	Exit();
	Wait();
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
		GameTime::GameSleep(1000);
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
	GameMsg		*msg = NULL;
	NetMessage	*recvQueue = m_net_manager.GetMsgQueue();
	unsigned long long		last_time_ms = GameTime::Instance().FrameTime();	// 上一次更新时间
	unsigned long long		cur_time_ms = 0;
	unsigned long long		second = 0;
	unsigned long long		oneMinute = 60000;

	std::thread log_thread(::WriteLog, this);
	std::thread listen_thread(::Listen, this);
// 	m_log_thread.Create(::WriteLog, this);
// 	m_listen_thread.Create(::Listen, this);
	bool cur_sleep_state = false;
	bool last_sleep_state = false;
	while (m_is_run)
	{
		if (recvQueue->Pop(msg))
		{
			if (msg != NULL)
			{
				if ((int)msg->handle >= (int)0)
				{
					this->Recv(msg);
				}
				// 内存交给下游处理
				// delete (*msg);
			}
		}	
		else
		{
			cur_sleep_state = !cur_sleep_state;
		}

		GameTime::Instance().Update();
		cur_time_ms = GameTime::Instance().FrameTime();
		if (cur_time_ms != last_time_ms)
		{
			UpdateAll(cur_time_ms - last_time_ms);
			last_time_ms = cur_time_ms;
		}
		else if (cur_sleep_state != last_sleep_state)
		{
			GameTime::GameSleep(m_sleep_time_ms);
			last_sleep_state = cur_sleep_state;
		}
		
	}
//	m_net_manager.Exit();
	log_thread.join();
	listen_thread.join();
//	m_listen_thread.Join();
//	Exit();
	return true;
}





