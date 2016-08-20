
#ifndef LOG_DB_H
#define LOG_DB_H

#include <vector>
#include <string>
#include "lib/include/thread/basethread.h"
#include "lib/include/db/base.h"
#include "lib/include/db/prepare.h"
#include "lib/include/base/export.h"
#include "lib/include/base/timer.h"
#include "common/serverdef.h"
#include "common/datastructure/gamevector.h"

// 有需要（性能）再将写文件和写数据库分开不同的线程

namespace LogMsg
{
	// log database message
	enum
	{
		LM_REGISTER = ThreadSysID::MAX_ID + 1,
		LM_WRITE_FILE_ERROR,
		LM_WRITE_FILE_INFO,
		LM_WRITE_DB
	};

	struct LogRegister
	{
		unsigned short	index;
		char			name[32];
		char 			fields[256];
		char 			format[256];
		unsigned short	interval;
		unsigned short 	max_num;
	};

	struct LogWrite
	{
		int len;
		// 日志数据
	};
}
	
#define LOG_DO(Len, ...)\
	void Do(std::string &log, const char *format){\
		char buf[Len]; \
		Make(log, buf, Len, format, __VA_ARGS__);\
	}

class LogDB
{
public:
	LogDB(unsigned short _index) :index(_index){}

	virtual void Do(std::string &log, const char *format) = 0;
	unsigned short index;
protected:
	void Make(std::string &log, char *buf, unsigned short len, const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		int ret = vsnprintf(buf, len, format, args);
		va_end(args); 
		log += buf;
	}
	
};

class Log : public BaseThread
{
public:
	Log(ThreadManager *manager, int log_num, const LogMsg::LogRegister reg[]);
	~Log();

	struct LogItem
	{
		unsigned short max_num;
		unsigned short cur_num = 0;
		std::string format;
		std::string default;
		std::string logs;
	};

	struct LogFile
	{
		unsigned short	num = 0;
		std::string		logs="";
	};
	
	bool	Init();
	void 	Save(unsigned short index);
protected:
	
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	void	Register(LogMsg::LogRegister *data);
	void	WriteDB(int len, const char *data);
	void	WriteFile(int len, char *data, char *format);
private:
	int				m_log_num;
	FILE			*m_fp;
	LogItem			*m_log_list;
	LogFile			m_log_file;
	TimerManager	*m_timer_manager;
	MysqlBase		m_mysql;		// todo 将mysql剥离出来，这样更方便生成dll
};

namespace New
{
	EXPORT Log * _LogDB(ThreadManager *manager, int log_num, const LogMsg::LogRegister reg[]);
}
#endif