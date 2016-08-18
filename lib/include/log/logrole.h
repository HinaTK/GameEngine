
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

namespace LogDBMsg
{
	// log database message
	enum
	{
		LDM_REGISTER = ThreadSysID::MAX_ID + 1,
		LDM_WRITE,
		LDM_ROLE_WRITE
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
		unsigned short	index;
		unsigned short	len;
		// log data
	};

	struct LogRoleWrite
	{
		unsigned short	index;
		RoleID			role_id;
		unsigned short	len;
		// log data
	};

	static const int LOG_WRITE_LEN = sizeof(LogWrite);
	static const int LOG_ROLE_WRITE_LEN = sizeof(LogRoleWrite);
}

#define LOG_MAKE(Log, Len, Format, ...)\
	char buf[Len]; \
	Make(Log, buf, Len, Format, __VA_ARGS__);
	

class LogMsg
{
public:
	LogMsg(unsigned short _index) :index(_index){}

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

class LogRole : public BaseThread
{
public:
	LogRole(ThreadManager *manager, int log_num, const LogDBMsg::LogRegister reg[]);
	~LogRole();

	struct LogItem
	{
		unsigned short max_num;
		unsigned short cur_num = 0;
		std::string format;
		std::string default;
		std::string logs;
	};

	static int MakeLog(unsigned short index, RoleID role_id, char *buf, char *format, ...);

	void 	Save(unsigned short index);
protected:
	
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	void	Register(LogDBMsg::LogRegister *data);
	void	Write(int len, const char *data);
	bool	Save(LogItem &item);
private:
	int				m_log_num;
	LogItem			*m_log_list;
	TimerManager	*m_timer_manager;
	MysqlBase		m_mysql;		// todo 将mysql剥离出来，这样更方便生成dll
};


#endif