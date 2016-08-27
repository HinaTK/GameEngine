
#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "lib/include/db/handler.h"
#include "lib/include/db/preparestatic.h"
#include "lib/include/db/fieldmanager.h"
#include "common/serverdef.h"

class DBThread;
class DBManager
{
public:
	DBManager(DBThread *t);
	~DBManager();

protected:
	DBThread		*m_thread;
	MysqlHandler	m_mysql;
	FieldManager 	m_field_manager;
};

#endif