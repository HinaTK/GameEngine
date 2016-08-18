
#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include <stdio.h>
#include "lib/include/log/logrole.h"
#include "common/serverdef.h"

#if _MSC_VER
#define snprintf _snprintf
#endif

class LogGold : public LogMsg
{
public:
	LogGold(RoleID _role_id, int _gold)
	: role_id(_role_id)
	, gold(_gold)
	{
		index = 0;
	}

	void Make(std::string &log)
	{
		char str[64];
	#if (defined _WIN32) || (defined _WIN64)
		snprintf(str, 64, "(%I64d, 'gold=%d')", gold);
	#elif
		snprintf(str, 64, "(%lld, 'gold=%d')", gold);
	#endif	
		log += str;
	}

	RoleID role_id;
	int gold;
};

namespace LogHandlerWrite
{
	void LogGold(ThreadManager &manager, ThreadID id, RoleID role_id, int gold);
}

namespace LogHandler
{
	typedef void (*HandleFunc)(unsigned short len, char *buf);

	void LogGold(unsigned short len, char *buf);
}

#endif

