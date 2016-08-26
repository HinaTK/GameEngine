
#ifndef MYSQL_PREPARE_STATIC_H
#define MYSQL_PREPARE_STATIC_H

#include "prepare.h"

class MysqlPrepareStatic : public MysqlPrepare
{
public:
	MysqlPrepareStatic(MysqlHandler *handler, unsigned char num, const char *sql, unsigned short sql_len = 0);
	virtual ~MysqlPrepareStatic(){}

	// reconnect
	enum
	{
		RE_BIND = 0x01,
		RE_EXECUTE = 0x02
	};

	bool	Init();

	bool	Execute(unsigned short = RE_BIND | RE_EXECUTE);

	

private:
	char 			*m_sql;
	unsigned short 	m_sql_len;
};

#endif