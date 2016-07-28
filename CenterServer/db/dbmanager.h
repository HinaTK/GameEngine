
#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "lib/include/db/handler.h"
#include "lib/include/db/prepare.h"
#include "common/serverdef.h"

class DBThread;
class DBManager
{
public:
	DBManager(DBThread *t);
	~DBManager();

	void	LoadRoleMaxID(ThreadID tid);
	void	LoadRole(ThreadID tid, int len, const char *data);
	void	SaveRoleMaxID(unsigned int max_id);
	void	SaveRole(ThreadID tid, int len, const char *data);

protected:
	DBThread		*m_thread;

	MysqlHandler	m_mysql;
	MysqlPrepare	m_role_s;
	MysqlPrepare	m_role_i;
	MysqlPrepare	m_role_max_id;
};

#endif