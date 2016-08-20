
#ifndef LOG_ONLINE_H
#define LOG_ONLINE_H

#include "lib/include/log/logrole.h"
#include "loghandler.h"
#include "common/serverdef.h"

class LogOnline : public LogMsg
{
public:
	LogGold(int _online, unsigned int _time)
		: LogMsg(LogHandler::LOG_ONLINE)
		, online(_online)
		, time(_time)
	{
	}

	LOG_DO(64, online, time);
	
	int online;
	unsigned int time;
};

#endif