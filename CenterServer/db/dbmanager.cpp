
#include "dbmanager.h"
#include "dbthread.h"
#include "message/threadproto.h"
#include "lib/include/db/result.h"
#include "lib/include/common/serverconfig.h"

DBManager::DBManager(DBThread *t)
: m_thread(t)
, m_mysql(
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

void DBManager::LoadRole(ThreadID tid, int len, const char *data)
{
	struct ThreadProto::LoadRole *lr = (struct ThreadProto::LoadRole *)data;
	m_role_s.BindInt(0, &lr->server_id);
	m_role_s.BindChar(1, lr->account);
	if (m_role_s.Execute())
	{
		ThreadProto::LoadRoleRet lrr;

		READ_RESULT_BEGIN(m_role_s);
		if (mr->Read(0, lrr.name, GAME_NAME_SIZE))
		{
			printf("the name is %s\n", lrr.name);
		}
		READ_RESULT_END();
		m_thread->GetManager()->SendMsg(ThreadProto::TP_LOAD_ROLE_RET, tid, sizeof(ThreadProto::LoadRoleRet), (const char *)&lrr, m_thread->GetID());
	}
}

