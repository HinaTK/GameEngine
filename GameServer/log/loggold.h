
#ifndef LOG_GOLD_H
#define LOG_GOLD_H

#include "lib/include/log/logrole.h"
#include "loghandler.h"
#include "common/serverdef.h"

class LogGold : public LogMsg
{
public:
	LogGold(RoleID _role_id, int _gold)
		: LogMsg(0)
		, role_id(_role_id)
		, gold(_gold)
	{
	}

	void Do(std::string &log, const char *format){ LOG_MAKE(log, 64, format, role_id, gold); }

	RoleID role_id;
	int gold;
};

#endif // !LOG_GOLD_H
