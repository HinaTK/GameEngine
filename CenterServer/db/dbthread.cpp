
#include "dbthread.h"
#include "threadproto.h"
#include "lib/include/mysql/mysql.h"
#include "lib/include/common/argsplit.h"

DBThread::~DBThread()
{

}

DBThread::DBThread(ThreadManager *manager)
: BaseThread(manager, ThreadManager::EXIT_NORMAL)
, m_db_manager(this)
{
	m_name = "db";
	SetSleepTime(10);
}

bool DBThread::Init()
{
	return m_db_manager.Init();
}

bool DBThread::Run()
{
	return false;
}

void DBThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case ThreadProto::TP_LOAD_ROLE_MAX_ID:
		m_db_manager.LoadRoleMaxID(sid);
		break;
	case ThreadProto::TP_LOAD_ROLE:
		m_db_manager.LoadRole(sid, len, data);
		printf("load role ... %d\n", GetID());
		break;
	case ThreadProto::TP_SAVE_ROLE_MAX_ID:
		m_db_manager.SaveRoleMaxID(*(unsigned int *)data);
		break;
	case ThreadProto::TP_SAVE_ROLE:
		m_db_manager.SaveRole(sid, len, data);
		break;
	default:
		break;
	}
}

bool DBThread::CMD(TPT type, ThreadID sid, int len, const char *data)
{
	char *buf;
	ArgSplit split((char *)data);
	split.GetArg(&buf);
	if (strcmp(buf, "test") == 0)
	{
		if (split.GetLeft(&buf))
		{
			int id = atoi(buf);
			m_db_manager.Test(id);
			return true;
		}
	}
	else if (strcmp(buf, "test2") == 0)
	{
		if (split.GetLeft(&buf))
		{
			int id = atoi(buf);
			m_db_manager.SaveRoleMaxID(id);
			return true;
		}
	}
	return false;
}
