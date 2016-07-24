
#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "lib/include/db/status.h"
#include "lib/include/db/prepare.h"
#include "common/serverdef.h"

class DBManager
{
public:
	DBManager();
	~DBManager();

	void	LoadRole(Account account, ServerID sid);

protected:
	MysqlStatus m_mysql;

	MysqlPrepare	m_role_s;
};

#endif