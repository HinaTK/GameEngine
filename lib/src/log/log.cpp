
#ifdef WIN32
#include <direct.h>
#endif
#ifdef __unix
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif
#include <time.h>
#include <stdio.h>
#include "log.h"
#include "libcommon/memorypool.h"

REGISTER_MEMORYPOOL(poolspace, Log, 16);

Log::Log(const char *server_name, const char *log_name)
: m_log_fp(NULL)
, m_root_dir(server_name)
, m_log_name(log_name)
{
	char path[512];
#ifdef WIN32
	_getcwd(path, 512);
	m_root_dir = path;
	m_root_dir = m_root_dir + "\\log";
	_mkdir(m_root_dir.c_str());
	m_root_dir = m_root_dir + "\\" + server_name;
	_mkdir(m_root_dir.c_str());
#endif
#ifdef __unix
	getcwd(path, 512);
	m_root_dir = path;
	m_root_dir = m_root_dir + "/log";
	mkdir(m_root_dir.c_str(), 0777);
	m_root_dir = m_root_dir + "/" + server_name;
	mkdir(m_root_dir.c_str(), 0777);
#endif
	do 
	{
		if (!MakeDayDir())
		{
			break;
		}
		if (!MakeHourDir())
		{
			break;
		}
		if (!MakeFile())
		{
			break;
		}
		return;
	} while (false);
	printf("Log Init error!!!\n");
}

Log::~Log()
{
	Flush();
	if (m_log_fp != NULL)
	{
		fclose(m_log_fp);
	}
}

#define PushLog()\
	char temp[1024] = { 0 }; \
	char logHeader[64] = { 0 }; \
	va_list args; \
	va_start(args, log); \
	vsprintf(temp, log, args); \
	va_end(args); \
	static tm *t = NULL;\
	static time_t gametime = 0;\
	time(&gametime);\
	t = localtime(&gametime);\
	sprintf(logHeader, format, t->tm_hour, t->tm_min, t->tm_sec); \
	std::string strLog = logHeader;\
	strLog = strLog + temp + "\n";\
	m_queue.Push(strLog);\


void Log::Normal(char *log, ...)
{
	static const char format[] = "%d:%d:%d (Normal): ";
	PushLog();
}

void Log::Warn(char *log, ...)
{
	static const char format[] = "%d:%d:%d (Warn): ";
	PushLog();
}

void Log::Error(char *log, ...)
{
	static const char format[] = "%d:%d:%d (Error): ";
	PushLog();
}

#define  RETURN_AND_CLEAR()\
	m_queue.Clear();\
	return;\

void Log::Flush()
{
	if (m_queue.IsEmpty())
	{
		return;
	}
	if (m_day != Day())
	{
		if (!MakeDayDir())
		{
			RETURN_AND_CLEAR();
		}
		if (!MakeHourDir())
		{
			RETURN_AND_CLEAR();
		}
		if (!MakeFile())
		{
			RETURN_AND_CLEAR();
		}
	}
	else if (m_hour != Hour())
	{
		if (!MakeHourDir())
		{
			RETURN_AND_CLEAR();
		}
		if (!MakeFile())
		{
			RETURN_AND_CLEAR();
		}
	}
	if (m_log_fp == NULL)
	{
		RETURN_AND_CLEAR();
	}
	do 
	{
		fprintf(m_log_fp, "%s", m_queue.Val()->c_str());
	} while (!m_queue.IsEmpty());
}

bool Log::MakeDayDir()
{
	char dir[32];
	m_day = Day();
#ifdef WIN32
	sprintf(dir, "\\%d", m_day);
	std::string temp = m_root_dir + dir;
	_mkdir(temp.c_str());
#endif
#ifdef __unix
	sprintf(dir, "/%d", m_day);
	std::string temp = m_root_dir + dir;
	mkdir(temp.c_str(), 0777);
#endif
	m_day_dir = dir;
	return true;
}

bool Log::MakeHourDir()
{
	char dir[32];
	m_hour = Hour();
#ifdef WIN32
	sprintf(dir, "\\%d", m_hour);
	std::string temp = m_root_dir + m_day_dir + dir;
	_mkdir(temp.c_str());
#endif
#ifdef __unix
	sprintf(dir, "/%d", m_hour);
	std::string temp = m_root_dir + m_day_dir + dir;
	mkdir(temp.c_str(), 0777);
#endif
	m_hour_dir = dir;
	return true;
}

bool Log::MakeFile()
{
#ifdef WIN32
	std::string strFile = m_root_dir + m_day_dir + m_hour_dir + "\\" + m_log_name;
#endif
#ifdef __unix
	std::string strFile = m_root_dir + m_day_dir + m_hour_dir + "/" + m_log_name;
#endif // __unix

	if (m_log_fp != NULL)
	{
		fclose(m_log_fp);
	}
	m_log_fp = fopen(strFile.c_str(), "a");
	if (m_log_fp == NULL)
	{
		return false;
	}
	return true;
}

int Log::Day()
{
	static tm     *t = NULL;
	static time_t gametime = 0;
	static int    day = 0;
	time(&gametime);
	t = localtime(&gametime);

	day = t->tm_mday;
	day = (t->tm_mon + 1) * 100 + day;
	day = (t->tm_year + 1900) * 10000 + day;
	return day;
}

int Log::Hour()
{
	static tm     *t = NULL;
	static time_t gametime = 0;
	time(&gametime);
	t = localtime(&gametime);
	return t->tm_hour;
}
