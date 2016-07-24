
#ifndef MYSQL_PREPARE_H
#define MYSQL_PREPARE_H

#include "lib/include/mysql/mysql.h"
#include "lib/include/common/memorypool.h"

class MysqlPrepare
{
public:
	MysqlPrepare(MYSQL *mysql, unsigned char num, char *sql, unsigned short sql_len = 0);
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
	inline bool	HasResult();
	bool	ReadResultBegin();
	bool	ReadResultEnd();

	MYSQL_STMT *GetStmt(){ return m_stmt; }
	MemoryPool *Get1Pool(){ return &m_1_pool; }
	MemoryPool *Get2Pool(){ return &m_2_pool; }
	MemoryPool *Get4Pool(){ return &m_4_pool; }
	MemoryPool *Get8Pool(){ return &m_8_pool; }
protected:
	MYSQL_BIND	*m_param;
	MYSQL_STMT	*m_stmt;
	MemoryPool	m_1_pool;
	MemoryPool	m_2_pool;
	MemoryPool	m_4_pool;
	MemoryPool	m_8_pool;
};

#endif