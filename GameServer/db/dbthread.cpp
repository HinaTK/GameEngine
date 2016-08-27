
#include "dbthread.h"
#include "module/rolemodule.h"
#include "module/role/test.h"
#include "protocol/proto.h"


FieldManager::CreateField fields[] =
{
	{ "test", []()->Field *{return new MTest(); } }
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
	return true;
}


bool DBThread::Run()
{
	return false;
}

void DBThread::RecvData(short type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case TProto::DB_SAVE_MODULE:
		if (data != NULL)
		{
			RoleModule *temp = (RoleModule *)data;
			temp->Exe(this);
			delete temp;
		}
		break;
	}
}


