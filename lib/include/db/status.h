
#ifndef MYSQL_STATUS_H
#define MYSQL_STATUS_H

#include "lib/include/mysql/mysql.h"
#include "lib/include/common/memorypool.h"

// todo 改名为MysqlHandle
class MysqlStatus
{
public:
	MysqlStatus(const char *ip, const char *user, const char *password, const char *db, unsigned short port);
	~MysqlStatus();

	MYSQL	*GetMysql(){ return m_mysql; }


	MemoryPool *Get1Pool(){ return &m_1_pool; }
	MemoryPool *Get2Pool(){ return &m_2_pool; }
	MemoryPool *Get4Pool(){ return &m_4_pool; }
	MemoryPool *Get8Pool(){ return &m_8_pool; }
protected:
	MYSQL *m_mysql;
	MemoryPool	m_1_pool;
	MemoryPool	m_2_pool;
	MemoryPool	m_4_pool;
	MemoryPool	m_8_pool;
};


#endif