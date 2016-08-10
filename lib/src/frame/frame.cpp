
#include <signal.h>
#include "frame.h"
#include "message.h"
#include "lib/include/thread/basethread.h"
#include "lib/include/common/argsplit.h"
#include "lib/include/base/function.h"


static Frame *g_frame;
namespace SignalCatch
{
	void Catch(int sig)
	{
		if (g_frame != NULL)
		{
			Function::Info("Catch exit signal %d", sig);
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
	char cmd_buf[512];
	char *buf;
	ArgSplit split("");
	while (IsRun())
	{
		memset(cmd_buf, 0, sizeof(cmd_buf));
		gets(cmd_buf);
		split.Reset(cmd_buf);
		split.GetArg(&buf);

		if (strcmp(cmd_buf, "exit") == 0)
		{
			SetExit();
		}
		else if (strcmp(cmd_buf, "ping") == 0)
		{
			// ping 一下所有线程，看是否有阻塞
			printf("ping ...\n");
		}
		else if (strcmp(buf, "thread") == 0)
		{
			if (!split.GetArg(&buf))
			{
				game::Array<BaseThread *> *threads = m_thread_manager.GetThreads();
				printf("%-10s %-32s\n", "thread id", "thread name");
				for (game::Array<BaseThread *>::iterator itr = threads->Begin(); itr != threads->End(); ++itr)
				{
					printf("%-10d %-32s\n", (*itr)->GetID(), (*itr)->GetName());
				}
			}
			else
			{
				int id = atoi(buf);
				if (split.GetLeft(&buf))
				{
					m_thread_manager.CMD(ThreadSysID::TSID_THREAD_CMD, INVALID_THREAD_ID, strlen(buf) + 1, buf, id);
				}
				else
				{
					m_thread_manager.CMD(ThreadSysID::TSID_THREAD_CMD, INVALID_THREAD_ID, 0, NULL, id);
				}
			}
		}
		else
		{
			if (!this->Cmd(cmd_buf))
			{
				printf("no this cmd: %s\n", cmd_buf);
			}
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



