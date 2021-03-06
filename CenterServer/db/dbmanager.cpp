
#include "dbmanager.h"
#include "dbthread.h"
#include "threadproto.h"
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
, m_role_s(&m_mysql, 2, "SELECT rid,name FROM role WHERE sid=? AND account=? LIMIT 1;")
, m_role_i(&m_mysql, 4, "INSERT INTO role (rid,sid,account,name) VALUES (?,?,?,?);")
, m_role_max_id(&m_mysql, 2, "REPLACE INTO ids (sid, role_id) VALUES (?,?);")
{
	
}

DBManager::~DBManager()
{

}

bool DBManager::Init()
{
	if (!m_mysql.Connect())
	{
		Function::Error("center can not connect mysql");
		m_mysql.Close();
		return false;
	}
	if (!m_role_s.Init() ||
		!m_role_i.Init() ||
		!m_role_max_id.Init())
	{
		return false;
	}
	return true;
}

void DBManager::LoadRoleMaxID(ThreadID tid)
{
	MysqlPrepareDynamic mp(&m_mysql, 1);
	mp.BindInt(0, &CenterConfig::Instance().sid);
	if (mp.Execute("SELECT role_id FROM ids WHERE sid=?;"))
	{
		unsigned int max_id = 1;
		MysqlResult mr(&mp);
		while (mp.HasResult())
		{
			mr.Read(0, max_id);
		}

		Function::Info("The max role id is %d", max_id);
		m_thread->GetManager()->SendMsg(tid, TProto::TP_LOAD_ROLE_MAX_ID_RET, sizeof(unsigned int), (const char *)&max_id, m_thread->GetID());
	}
}

void DBManager::LoadRole(ThreadID tid, int len, const char *data)
{
	struct TProto::LoadRole *lr = (struct TProto::LoadRole *)data;
	m_role_s.BindInt(0, &lr->sid);
	m_role_s.BindChar(1, lr->account);
	if (m_role_s.Execute())
	{
		int num = 0;
		TProto::LoadRoleRet lrr;
		MysqlResult mr(&m_role_s);
		while(m_role_s.HasResult())
		{
			if (!mr.Read(0, lrr.rid))
			{
				// todo wirte log
			}
			if (!mr.Read(1, lrr.name, GAME_NAME_SIZE))
			{
				// todo wirte log
			}
			++num;
		}
		if (num > 0)
		{
			lr->handle;
			m_thread->GetManager()->SendMsg(tid, TProto::TP_LOAD_ROLE_RET, sizeof(TProto::LoadRoleRet), (const char *)&lrr, m_thread->GetID());
		}
		else
		{
			m_thread->GetManager()->SendMsg(tid, TProto::TP_LOAD_ROLE_NONE, lr->handle);
		}
	}
}

void DBManager::SaveRoleMaxID(unsigned int max_id)
{
	m_role_max_id.BindInt(0, &CenterConfig::Instance().sid);
	m_role_max_id.BindUInt(1, &max_id);
	if (!m_role_max_id.Execute())
	{
		// todo 写log
	}
}

void DBManager::SaveRole(ThreadID tid, int len, const char *data)
{
	struct TProto::SaveRole *sr = (TProto::SaveRole *)data;
	m_role_i.BindLong(0, &sr->rid);
	m_role_i.BindInt(1, &sr->sid);
	m_role_i.BindVarChar(2, sr->account);
	m_role_i.BindChar(3, sr->name);
	if (!m_role_i.Execute())
	{
		// todo 写log
	}
	else
	{
		TProto::SaveRoleRet srr;
		srr.handle = sr->handle;
		srr.rid = sr->rid;
		srr.sid = sr->sid;
		memcpy(srr.name, sr->name, GAME_NAME_SIZE);
		m_thread->GetManager()->SendMsg(tid, TProto::TP_SAVE_ROLE_RET, sizeof(TProto::SaveRoleRet), (const char *)&srr, m_thread->GetID());
	}
}


void DBManager::Test(int id)
{
	MysqlPrepareDynamic mp(&m_mysql, 1);
	mp.BindInt(0, &id);
	if (mp.Execute("INSERT INTO test (dd) VALUES (?);"))
	{
		
	}
}
