
#ifndef LOG_DB_H
#define LOG_DB_H

#include <vector>
#include <string>
#include "lib/include/thread/basethread.h"
#include "lib/include/db/handler.h"
#include "lib/include/db/prepare.h"
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


class LogDB : public BaseThread
{
public:
	LogDB(ThreadManager *manager, int log_num);
	~LogDB();

	struct LogItem
	{
		LogItem() :logs(32){}
		std::string db_name;
		game::Vector<std::string> logs;
	};

	static int MakeJson(char *buf, char *format, ...);

protected:
	bool	Init();
	bool	Ready();
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	void	Register(LogDBMsg::LogRegister *data);
	void	Write(int len, const char *data);
	void	RoleWrite(int len, const char *data);
private:
	int				m_log_num;
	LogItem			*m_log_list;
	MysqlHandler	m_mysql;
};



#endif