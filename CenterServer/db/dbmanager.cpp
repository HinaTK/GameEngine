
#include "dbmanager.h"
#include "message/threadproto.h"
#include "lib/include/db/result.h"
#include "lib/include/common/serverconfig.h"

DBManager::DBManager()
: m_mysql(
CenterConfig::Instance().db.ip,
CenterConfig::Instance().db.user.c_str(),
CenterConfig::Instance().db.passwd.c_str(),
CenterConfig::Instance().db.dbname.c_str(),
CenterConfig::Instance().db.port)
, m_role_s(&m_mysql, 2, "SELECT name FROM role WHERE sid=? AND account=?;")
{

}

DBManager::~DBManager()
{

}

void DBManager::LoadRole(int len, const char *data)
{
	struct ThreadProto::LoadRole *lr = (struct ThreadProto::LoadRole *)data;
	m_role_s.BindInt(0, lr->server_id);
	m_role_s.BindChar(1, lr->account);
	if (m_role_s.Execute())
	{
		GameName name;
		READ_RESULT_BEGIN(m_role_s);
		if (mr->Read(0, name, GAME_NAME_SIZE))
		{
			printf("the name is %s\n", name);
		}

		READ_RESULT_END();
	}
}

void DBManager::LoadRole(Account account, ServerID sid)
{
	m_role_s.BindInt(0, sid);
	m_role_s.BindChar(1, account);
	if (m_role_s.Execute())
	{
		GameName name;
		READ_RESULT_BEGIN(m_role_s);
		if (mr->Read(0, name, GAME_NAME_SIZE))
		{
			printf("the name is %s\n", name);
		}
		
		READ_RESULT_END();
	}
}

