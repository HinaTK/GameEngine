
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
		if (g_frame != NULL && g_frame->IsRun())
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
	int cur_id = -1;		// 当前操作的线程
	ArgSplit split("");
	while (IsRun())
	{
		memset(cmd_buf, 0, sizeof(cmd_buf));
		gets(cmd_buf);
		split.Reset(cmd_buf);
		if (!split.GetArg(&buf))
		{
			continue;
		}

		if (strcmp(cmd_buf, "exit") == 0)
		{
			SetExit();
		}
		else if (strcmp(cmd_buf, "reset") == 0)
		{
			cur_id = -1;
		}
		else if (strcmp(buf, "status") == 0)
		{
			printf("the current id is %d\n", cur_id);
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
				else goto NO_CMD;
			}
		}
		else if (strcmp(buf, "use") == 0)
		{
			if (split.GetArg(&buf))
			{
				cur_id = atoi(buf);
			}
			else goto NO_CMD;
		}
		else if (cur_id >= 0)
		{
			m_thread_manager.CMD(ThreadSysID::TSID_THREAD_CMD, INVALID_THREAD_ID, strlen(cmd_buf) + 1, cmd_buf, cur_id);
		}
		else if (!this->Cmd(cmd_buf))
		{
			goto NO_CMD;
		}
		continue;
NO_CMD:;
		printf("No this cmd: %s\n", cmd_buf);		
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



