
#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "lib/include/db/handler.h"
#include "lib/include/db/preparestatic.h"
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

	void	Test(int id);

protected:
	DBThread		*m_thread;

	MysqlHandler		m_mysql;
	MysqlPrepareStatic	m_role_s;
	MysqlPrepareStatic	m_role_i;
	MysqlPrepareStatic	m_role_max_id;
};

#endif