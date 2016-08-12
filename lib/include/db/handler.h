
#ifndef MYSQL_STATUS_H
#define MYSQL_STATUS_H

#include "lib/include/mysql/mysql.h"
#include "lib/include/mysql/errmsg.h"
#include "lib/include/common/memorypool.h"

// todo 改名为MysqlHandle
class MysqlHandler
{
public:
	MysqlHandler(const char *ip, const char *user, const char *password, const char *db, unsigned short port);
	~MysqlHandler();

	MYSQL	*GetMysql(){ return m_mysql; }

	bool		Connect();
	bool		Reconnect();
	void		Close();


	MemoryPool *Get1Pool(){ return &m_1_pool; }
	MemoryPool *Get2Pool(){ return &m_2_pool; }
	MemoryPool *Get4Pool(){ return &m_4_pool; }
	MemoryPool *Get8Pool(){ return &m_8_pool; }
protected:
	MYSQL *m_mysql;

	char m_host[32];
	char m_user[32];
	char m_passwd[32];
	char m_db[32];
	unsigned short m_port;

	MemoryPool	m_1_pool;
	MemoryPool	m_2_pool;
	MemoryPool	m_4_pool;
	MemoryPool	m_8_pool;
};


#endif