
#ifndef MYSQL_STATUS_H
#define MYSQL_STATUS_H

#include "lib/include/mysql/mysql.h"

class MysqlStatus
{
public:
	MysqlStatus(const char *ip, const char *user, const char *password, const char *db);
	~MysqlStatus();

	MYSQL	*GetMysql(){ return m_mysql; }
protected:
	MYSQL *m_mysql;
};


#endif