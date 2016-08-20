
#ifndef LOG_GOLD_H
#define LOG_GOLD_H

#include "lib/include/log/logdb.h"
#include "loghandler.h"
#include "common/serverdef.h"

class LogGold : public LogDB
{
public:
	LogGold(RoleID _role_id, int _gold)
		: LogDB(LogHandler::LOG_GOLD)
		, role_id(_role_id)
		, gold(_gold)
	{
	}

	LOG_DO(64, role_id, gold);

	RoleID role_id;
	int gold;
};

#endif // !LOG_GOLD_H

