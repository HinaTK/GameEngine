
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
		}

		if (sig != SIGINT)
		{
			signal(sig, SIG_DFL);
		}
		else
		{
			signal(SIGINT, SignalCatch::Catch);
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
#if (defined _WIN32) || (defined _WIN64)
	SetConsoleCtrlHandler(CosonleHandler, TRUE);
#endif	
#ifdef __unix
	signal(SIGINT, SignalCatch::Catch);
	signal(SIGSEGV, SignalCatch::Catch);
	signal(SIGTERM, SignalCatch::Catch);
	signal(SIGABRT, SignalCatch::Catch);
	signal(SIGPIPE, SIG_IGN); // socket send if close
#endif
    
}

Frame::~Frame()
{
	
}

// 如果信号中断会保存现场，这里可以简化，避免死锁
void Frame::SetExit()
{
	if (m_is_run)
	{
		m_is_run = false;
		m_thread_manager.Exit();	
	}
}

void Frame::Run()
{
	static const int buf_size = 512;
	char cmd_buf[buf_size];
	char *buf;
	int cur_id = -1;		// 当前操作的线程
	ArgSplit split("");
#ifdef __unix
	int flags = fcntl(socket, F_GETFL, 0);
	/* 设置为非阻塞*/
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
#endif // __unix

	while (IsRun())
	{
#ifdef __unix
		Time::Sleep(20);
		int len = read(STDIN_FILENO, cmd_buf, buf_size);
		if (len < 1) continue;
		len = len > buf_size ? buf_size : len;
		cmd_buf[len - 1] = 0;
#endif // __unix
#if (defined _WIN32) || (defined _WIN64)
		memset(cmd_buf, 0, sizeof(cmd_buf));
		gets(cmd_buf);
#endif
		split.Reset(cmd_buf);
		if (!split.GetArg(&buf))
		{
			continue;
		}

		if (strcmp(cmd_buf, "exit") == 0)
		{
			SetExit();
		}
		else if (strcmp(buf, "ping") == 0)
		{
			if (!split.GetLeft(&buf))
			{
				game::Array<BaseThread *> *threads = m_thread_manager.GetThreads();
				for (game::Array<BaseThread *>::iterator itr = threads->Begin(); itr != threads->End(); ++itr)
				{
					printf("ping %d %s\n", (*itr)->GetID(), (*itr)->GetName());
					m_thread_manager.CMD(ThreadSysID::TSID_THREAD_CMD, INVALID_THREAD_ID, sizeof("ping"), "ping", (*itr)->GetID());
				}
			}
			else
			{
				int id = atoi(buf);
				printf("ping %d\n", id);
				m_thread_manager.CMD(ThreadSysID::TSID_THREAD_CMD, INVALID_THREAD_ID, sizeof("ping"), "ping", id);
			}
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

	Exit();
	m_thread_manager.Wait();
	Wait();
}




