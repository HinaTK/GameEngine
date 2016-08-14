
#ifndef MYSQL_PREPARE_DYNAMIC_H
#define MYSQL_PREPARE_DYNAMIC_H

#include "prepare.h"

class MysqlPrepareDynamic : public MysqlPrepare
{
public:
	MysqlPrepareDynamic(MysqlHandler *handler, unsigned char num);
	virtual ~MysqlPrepareDynamic(){}

	bool	Execute(char *sql){ return Execute(sql, strlen(sql)); }
	bool	Execute(char *sql, unsigned short sql_len);
private:
};

#endif