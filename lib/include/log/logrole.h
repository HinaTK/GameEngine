
#ifndef LOG_DB_H
#define LOG_DB_H

#include <vector>
#include <string>
#include "lib/include/thread/basethread.h"
#include "lib/include/db/base.h"
#include "lib/include/db/prepare.h"
#include "lib/include/base/export.h"
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
		short	index;
		char	name[32];
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


class LogRole : public BaseThread
{
public:
	LogRole(ThreadManager *manager, int log_num, LogDBMsg::LogRegister *reg);
	~LogRole();

	static const int SAVE_INTERVAL = 10;
	struct LogItem
	{
		std::string default;
		std::string logs;
	};

	static int MakeLog(unsigned short index, RoleID role_id, char *buf, char *format, ...);

	bool	Init();
	bool	Ready();
protected:
	
	
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	void	Register(LogDBMsg::LogRegister *data);
	void	Write(int len, const char *data);
	void	RoleWrite(int len, const char *data);
	bool	Save(LogItem &item);
private:
	int				m_log_num;
	LogItem			*m_log_list;
	time_t			m_next_time;
	MysqlBase		m_mysql;

};


#endif