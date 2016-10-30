
#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include "lib/include/base/log.h"
#include "common/serverdef.h"

#define LogNew(Class) \
	(char *) new Class

namespace LogHandler
{
	enum
	{
		LOG_GOLD = 0,
		LOG_ONLINE,
		LOG_MAX
	};

	static const LogMsg::LogRegister reg[] =
	{
		{ LOG_GOLD, 	"log_gold", 	"(rid,log)", 		"(%lld, 'gold=%d')", 	10, 1000 },
		{ LOG_ONLINE, 	"log_online", 	"(online, time)", 	"(%d, %d)", 			10, 1000 }
	};


	void DB(ThreadManager &manager, ThreadID id, char * log)
	{
		ThreadMsg msg;
		msg.type = LogMsg::LM_WRITE_DB;
		msg.data = log;
		manager.SendMsg(id, msg);
	}

	inline void Error(ThreadManager &manager, ThreadID id, char *data)
	{
		manager.SendMsg(id, LogMsg::LM_WRITE_FILE_ERROR, strlen(data) + 1, data, INVALID_THREAD_ID);
	}

	inline void Info(ThreadManager &manager, ThreadID id, char *data)
	{
		manager.SendMsg(id, LogMsg::LM_WRITE_FILE_INFO, strlen(data) + 1, data, INVALID_THREAD_ID);
	}
}

#endif

