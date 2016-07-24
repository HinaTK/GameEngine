
#include "dbmanager.h"
#include "lib/include/db/result.h"
#include "lib/include/common/serverconfig.h"

DBManager::DBManager()
: m_mysql(
CenterConfig::Instance().db.ip,
CenterConfig::Instance().db.user.c_str(),
CenterConfig::Instance().db.passwd.c_str(),
CenterConfig::Instance().db.dbname.c_str(),
CenterConfig::Instance().db.port)
, m_role_s(m_mysql.GetMysql(), 2, "SELECT * FROM role WHERE account=? AND sid=?;")
{

}

DBManager::~DBManager()
{

}

void DBManager::LoadRole(Account account, ServerID sid)
{
	if (m_role_s.Execute())
	{
		MysqlResult *mr = new MysqlResult(&m_role_s);
		while (m_role_s.HasResult())
		{

		}
		// read result
	}
}

