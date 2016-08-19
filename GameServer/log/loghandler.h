
#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include "lib/include/log/logdb.h"
#include "common/serverdef.h"


namespace LogHandler
{
	enum
	{
		LOG_GOLD = 0,
		LOG_ONLINE,
		LOG_MAX
	};

	static const LogDBMsg::LogRegister reg[] =
	{
		{ LOG_GOLD, 	"log_gold", 	"(rid,log)", 		"(%lld, 'gold=%d')", 	10, 1000 },
		{ LOG_ONLINE, 	"log_online", 	"(online, time)", 	"(%d, %d)", 			10, 1000 }
	};

	template <typename T>
	void Write(ThreadManager &manager, ThreadID id, T log)
	{
		ThreadMsg msg;
		msg.type = LogDBMsg::LDM_WRITE;
		//msg.length = sizeof(T);
		msg.data = (char *)log;
		manager.SendMsg(id, msg);
	}
}

#endif

