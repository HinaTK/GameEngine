
#include <signal.h>
#include "frame.h"
#include "lib/include/thread/basethread.h"
#include "lib/include/common/argsplit.h"
#include "lib/include/common/message.h"
#include "lib/include/base/function.h"
#include "lib/include/base/interface.h"

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

#include <dbghelp.h>
#include <sys/stat.h>
#include <shellapi.h> 

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

char g_exe_file_path[512];
char g_dump_file_name[512];

typedef BOOL(WINAPI *MINIDUMPWRITEDUMP) (
	HANDLE hProcess,
	DWORD ProcessId,
	HANDLE hFile,
	MINIDUMP_TYPE DumpType,
	const PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
	const PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
	const PMINIDUMP_CALLBACK_INFORMATION CallbackParam
	);

static LPTOP_LEVEL_EXCEPTION_FILTER last_filter = 0;
static MINIDUMP_TYPE g_dump_type = MiniDumpWithIndirectlyReferencedMemory;

const char *ErrorReportFile = "errorrpt.exe";

static void create_default_info(char *temp, PEXCEPTION_RECORD pRec)
{
	::_snprintf(temp, sizeof(temp), "Exception Code: %X, at address %p", pRec->ExceptionCode, pRec->ExceptionAddress);
}

LONG WINAPI _except_filter(EXCEPTION_POINTERS *pExcp)
{
	char temp[4096];
	const char* help_dll = "dbghelp.dll";

	MINIDUMP_EXCEPTION_INFORMATION excp_info = { GetCurrentThreadId(), pExcp, FALSE };
	PEXCEPTION_RECORD pRec = pExcp->ExceptionRecord;
	HMODULE hDll = NULL;
	hDll = ::LoadLibrary(help_dll);
	char filename[MAX_PATH];
	if (hDll)
	{
		MINIDUMPWRITEDUMP pDump = (MINIDUMPWRITEDUMP)::GetProcAddress(hDll, "MiniDumpWriteDump");
		if (pDump)
		{
			time_t rawtime;
			time(&rawtime);
			struct tm *timeinfo = localtime(&rawtime);
			::strftime(filename, MAX_PATH, "-%Y%m%d-%H%M%S-0.dmp", timeinfo);
			::strcat(g_dump_file_name, filename);
			for (int i = 0; i < 10; ++i)
			{
				g_dump_file_name[::strlen(g_dump_file_name) - 5] = i + 48;
				struct _stat sb;
				if (_stat(g_dump_file_name, &sb) != 0)
				{
					break;
				}
			}

			HANDLE hFile = ::CreateFile(g_dump_file_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile)
			{
				DWORD buf[256];
				DWORD *p = buf;
				MINIDUMP_USER_STREAM user_stream[1];
				user_stream[0].Type = 0x10001;
				user_stream[0].BufferSize = (DWORD)(p - buf) * sizeof(DWORD);
				user_stream[0].Buffer = buf;
				MINIDUMP_USER_STREAM_INFORMATION user_info;
				user_info.UserStreamCount = 1;
				user_info.UserStreamArray = user_stream;
				pDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, g_dump_type, &excp_info, &user_info, NULL);
				::CloseHandle(hFile);
				::_snprintf(temp, sizeof(temp),
					"非常遗憾的通知您，程序内部发生了不可挽回的错误。\n"
					"幸运的是这个错误已经被记录到\n\t%s%s\n文件里。\n\n"
					"Exception Code: %X, at address %p",
					g_exe_file_path, g_dump_file_name, pRec->ExceptionCode, pRec->ExceptionAddress);
			}
			else
			{
				create_default_info(temp, pRec);
			}
		}
		else
		{
			create_default_info(temp, pRec);
		}
	}
	else
	{
		create_default_info(temp, pRec);
	}
	::MessageBox(0, temp, "异常错误", MB_OK | MB_ICONSTOP);
	if (last_filter)
	{
		last_filter(pExcp);
	}
	ShellExecute(0, "open", ErrorReportFile, filename, 0, SW_SHOW);
	return EXCEPTION_CONTINUE_SEARCH;
}

void start_except_catch()
{
	GetModuleFileName(GetModuleHandle(NULL), g_exe_file_path, MAX_PATH);
	std::string str = g_exe_file_path;
	size_t pos = str.find_last_of('\\');
	size_t pos2 = str.find_last_of('.');
	g_exe_file_path[pos2] = 0;
	strcpy(g_dump_file_name, g_exe_file_path + pos + 1);
	g_exe_file_path[pos + 1] = 0;
	if (!last_filter)
	{
		::SetErrorMode(SEM_NOGPFAULTERRORBOX);
		last_filter = ::SetUnhandledExceptionFilter(_except_filter);
	}
}

void stop_except_catch()
{
	::SetErrorMode(0);
	::SetUnhandledExceptionFilter(last_filter);
}
#endif


Frame::Frame()
: m_is_run(true)
{
	g_frame = this;
#if (defined _WIN32) || (defined _WIN64)
	SetConsoleCtrlHandler(CosonleHandler, TRUE);
	start_except_catch();
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
	stop_except_catch();
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
	Time::Sleep(1000);
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
			Function::CMD();
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
					Function::CMD("ping %d %s", (*itr)->GetID(), (*itr)->GetName());
					m_thread_manager.CMD(ThreadSysID::TSID_THREAD_CMD, INVALID_THREAD_ID, sizeof("ping"), "ping", (*itr)->GetID());
				}
			}
			else
			{
				int id = atoi(buf);
				Function::CMD("ping %d", id);
				m_thread_manager.CMD(ThreadSysID::TSID_THREAD_CMD, INVALID_THREAD_ID, sizeof("ping"), "ping", id);
			}
		}
		else if (strcmp(cmd_buf, "reset") == 0)
		{
			cur_id = -1;
			Function::CMD("the current thread is main thread");
		}
		else if (strcmp(buf, "status") == 0)
		{
			Function::CMD("the current thread is %d", cur_id);
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
				Function::CMD();
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
				Function::CMD("the current thread is %d", cur_id);
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
		Function::CMD("No this cmd: %s", cmd_buf);	
	}

	Exit();
	m_thread_manager.Wait();
	Wait();
}




