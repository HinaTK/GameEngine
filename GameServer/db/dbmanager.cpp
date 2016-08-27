
#include "dbmanager.h"
#include "dbthread.h"
#include "db/module/test.h"
#include "lib/include/db/result.h"
#include "lib/include/db/preparedynamic.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/base/function.h"

FieldManager::CreateField fields[] =
{
	{"test", []()->Field *{return new MTest();}}
};

DBManager::DBManager(DBThread *t)
: m_thread(t)
, m_mysql(
CenterConfig::Instance().db.ip,
CenterConfig::Instance().db.user.c_str(),
CenterConfig::Instance().db.passwd.c_str(),
CenterConfig::Instance().db.dbname.c_str(),
CenterConfig::Instance().db.port)
, m_field_manager(&m_mysql, "role_moudle", sizeof(fields) / sizeof(FieldManager::CreateField), fields)
{

}

DBManager::~DBManager()
{

}
