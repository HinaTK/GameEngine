
#include <signal.h>
#include "frame.h"
#include "message.h"


static Frame *g_frame;
namespace SignalCatch
{
	void Catch(int sig)
	{
		if (g_frame != NULL)
		{
			g_frame->SetExit();
			signal(sig, SignalCatch::Catch);
		}
	}
}

// windows 控制台关闭监听
#if (defined _WIN32) || (defined _WIN64)
BOOL CALLBACK CosonleHandler(DWORD ev)
{
	BOOL bRet = FALSE;
	switch (ev)
	{
	case CTRL_CLOSE_EVENT:
		g_frame->SetExit();
		bRet = TRUE;
		break;
	default:
		break;
	}
	return bRet;
}
#endif


Frame::Frame()
: m_is_run(true)
{
	g_frame = this;
	signal(SIGINT, SignalCatch::Catch);
	signal(SIGSEGV, SignalCatch::Catch);
	signal(SIGTERM, SignalCatch::Catch);
	signal(SIGABRT, SignalCatch::Catch);
#if (defined _WIN32) || (defined _WIN64)
	SetConsoleCtrlHandler(CosonleHandler, TRUE);
#endif	
#ifdef __unix
	signal(SIGPIPE, SIG_IGN); // socket send if close
#endif
    
}

Frame::~Frame()
{
	
}


void Frame::Run()
{
	char cmd_buf[512] = { 0 };
	while (IsRun())
	{
		gets(cmd_buf);
		if (strcmp(cmd_buf, "exit") == 0)
		{
			SetExit();
		}
		else if (strcmp(cmd_buf, "ping") == 0)
		{
			// ping 一下所有线程，看是否有阻塞
			printf("ping ...\n");
		}
		else
		{
			this->Cmd(cmd_buf);
		}
	}
	
}

void Frame::SetExit()
{
	if (m_is_run)
	{
		m_is_run = false;
		m_thread_manager.Exit();
		Exit();
		m_thread_manager.Wait();
		Wait();
	}
}



