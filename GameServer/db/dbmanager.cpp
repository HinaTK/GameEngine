
#include "dbmanager.h"
#include "dbthread.h"
#include "lib/include/db/result.h"
#include "lib/include/db/preparedynamic.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/base/function.h"



DBManager::DBManager(DBThread *t)
: m_thread(t)
, m_mysql(
CenterConfig::Instance().db.ip,
CenterConfig::Instance().db.user.c_str(),
CenterConfig::Instance().db.passwd.c_str(),
CenterConfig::Instance().db.dbname.c_str(),
CenterConfig::Instance().db.port)

{

}

DBManager::~DBManager()
{

}
