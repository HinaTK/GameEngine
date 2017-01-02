
#ifndef MYSQL_BASE_H
#define MYSQL_BASE_H

#include "lib/include/mysql/mysql.h"
#include "lib/include/mysql/errmsg.h"

class MysqlBase
{
public:
	MysqlBase(const char *ip, const char *user, const char *password, const char *db, unsigned short port);
	virtual ~MysqlBase();

	MYSQL	*GetMysql(){ return m_mysql; }

	bool		Connect();
	bool		Reconnect();
	void		Close();

protected:
	MYSQL *m_mysql;

	char m_host[32];
	char m_user[32];
	char m_passwd[32];
	char m_db[32];
	unsigned short m_port;
};

#endif