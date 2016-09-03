
#include "dbthread.h"
#include "module/rolemodule.h"
#include "module/role/test.h"
#include "protocol/tproto.h"

#define NewField(Class) \
	[]()->Field *{return new Class(); }

FieldManager::CreateField fields[] =
{
	{ "test", NewField(MTest) }
};

DBThread::DBThread(ThreadManager *thread_manager)
: BaseThread(thread_manager, ThreadManager::EXIT_NORMAL)
, m_db_manager(this)
, m_field_manager(m_db_manager.GetMysql(), "role_module", sizeof(fields) / sizeof(FieldManager::CreateField), fields)
{
	m_name = "db";
	SetSleepTime(10);
}

DBThread::~DBThread()
{

}

bool DBThread::Init()
{
	if (!m_db_manager.Init() || !m_field_manager.Init())
	{
		return false;
	}
	return true;
}


bool DBThread::Run()
{
	return false;
}

void DBThread::RecvData(TPT type, ThreadID stid, int len, const char *data)
{
	switch (type)
	{
	case TProto::DB_LOAD_MODULE:
		RoleModule *rm = new RoleModule();
		rm->rf.rid = (RoleID)data;
		if (!m_field_manager.Load(&rm->rf))
		{
			delete rm;
		}
		GetManager()->SendMsg(stid, rm);
		break;
	}
}


