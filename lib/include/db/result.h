
#ifndef MYSQL_RESULT_H
#define MYSQL_RESULT_H

#include "lib/include/mysql/mysql.h"

class MysqlPrepare;
class MysqlResult
{
public:
	MysqlResult(MysqlPrepare *prepare);
	~MysqlResult();

	MYSQL_BIND *result;

private:
	MYSQL_RES *m_metadata;
};

#endif