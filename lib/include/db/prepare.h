
#ifndef MYSQL_PREPARE_H
#define MYSQL_PREPARE_H

#include "lib/include/mysql/mysql.h"
#include "lib/include/common/memorypool.h"

class MysqlHandler;
class MysqlPrepare
{
public:
	MysqlPrepare(MysqlHandler *handle, unsigned char num, char *sql, unsigned short sql_len = 0);
	virtual ~MysqlPrepare();

	void	BindTinyInt(unsigned char num, char val);
	void	BindSmallInt(unsigned char num, short val);
	void	BindInt(unsigned char num, int val);
	void	BindLong(unsigned char num, long long val);
	void	BindFloat(unsigned char num, float val);
	void	BindChar(unsigned char num, char *val);
	void	BindChar(unsigned char num, char *val, unsigned int length);
	void	BindVarChar(unsigned char num, char *val);
	void	BindVarChar(unsigned char num, char *val, unsigned int length);
	void	BindText(unsigned char num, char *val);
	void	BindText(unsigned char num, char *val, unsigned int length);

	bool	Execute();
	
	// 以下用结果集返回
	inline bool	HasResult() {if (mysql_stmt_fetch(m_stmt) == 0) return true; else return false;}
	bool	ReadResultBegin();
	bool	ReadResultEnd();

	MysqlHandler *GetHandle(){return m_handle;}
	MYSQL_STMT 	*GetStmt(){ return m_stmt; }
protected:
	MysqlHandler *m_handle;
	MYSQL_BIND	*m_param;
	MYSQL_STMT	*m_stmt;
};

#endif