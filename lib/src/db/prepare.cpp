
#include <stdio.h>
#include "prepare.h"
#include "handler.h"
#include "lib/include/base/function.h"

MysqlPrepare::MysqlPrepare(MysqlHandler *handler, unsigned char num, char *sql, unsigned short sql_len)
: m_handler(handler)
, m_param(NULL)
{
	m_sql_len == 0 ? m_sql_len = strlen(sql) : 0;
	m_sql = new char[m_sql_len];
	if (num > 0)
	{
		m_param = new MYSQL_BIND[num];
		memset(m_param, 0, sizeof(MYSQL_BIND)* num);
	}
	Init();
}

MysqlPrepare::~MysqlPrepare()
{
	if (m_param != NULL)
	{
		delete []m_param;
		m_param = NULL;
	}

	if (m_sql != NULL)
	{
		delete []m_sql;
		m_sql = NULL;
	}

	Close();
}

bool MysqlPrepare::Init()
{
	m_stmt = mysql_stmt_init(m_handler->GetMysql());

	if (m_stmt == NULL)
	{
		// A pointer to a MYSQL_STMT structure in case of success. NULL if out of memory.
		Function::Info("mysql_stmt_init error %s", m_sql);
		return false;
	}
	
	if (mysql_stmt_prepare(m_stmt, m_sql, m_sql_len) != 0)
	{
		Function::Info("mysql_stmt_prepare error %s", m_sql);
		Function::Info("%s", mysql_stmt_error(m_stmt));
		return false;
	}

	

	return true;
}


bool MysqlPrepare::Execute()
{
	if (mysql_stmt_bind_param(m_stmt, m_param) != 0)
	{
		Function::Info("mysql_stmt_bind_param error %s", mysql_stmt_error(m_stmt));
		return false;
	}

	int ret = mysql_stmt_execute(m_stmt);
	if (ret != 0)
	{
		if (ret == CR_SERVER_LOST)
		{
			// todo 断线重连
		}
		Function::Info("mysql_stmt_execute error %s", mysql_stmt_error(m_stmt));
		return false;
	}
	return true;
}

void MysqlPrepare::Close()
{
	if (m_stmt != NULL)
	{
		mysql_stmt_close(m_stmt);
		m_stmt = NULL;
	}
}


void MysqlPrepare::BindTinyInt(unsigned char num, char *val)
{
	m_param[num].buffer_type = MYSQL_TYPE_TINY;
	m_param[num].buffer = val;
}

void MysqlPrepare::BindSmallInt(unsigned char num, short *val)
{
	m_param[num].buffer_type = MYSQL_TYPE_SHORT;
	m_param[num].buffer = val;
}

void MysqlPrepare::BindInt(unsigned char num, int *val)
{
	m_param[num].buffer_type = MYSQL_TYPE_LONG;
	m_param[num].buffer = val;
	//m_param[num].length = 0;
}

void MysqlPrepare::BindUInt(unsigned char num, unsigned int *val)
{
	m_param[num].buffer_type = MYSQL_TYPE_LONG;
	m_param[num].buffer = val;
}

void MysqlPrepare::BindLong(unsigned char num, long long *val)
{
	m_param[num].buffer_type = MYSQL_TYPE_LONGLONG;
	m_param[num].buffer = val;
}

void MysqlPrepare::BindFloat(unsigned char num, float *val)
{
	m_param[num].buffer_type = MYSQL_TYPE_FLOAT;
	m_param[num].buffer = val;
}

void MysqlPrepare::BindChar(unsigned char num, char *val)
{
	m_param[num].buffer_type = MYSQL_TYPE_STRING;
	m_param[num].buffer = val;
	m_param[num].buffer_length = strlen(val);
}

void MysqlPrepare::BindChar(unsigned char num, char *val, unsigned int length)
{
	m_param[num].buffer_type = MYSQL_TYPE_STRING;
	m_param[num].buffer = val;
	m_param[num].buffer_length = length;
}

void MysqlPrepare::BindVarChar(unsigned char num, char *val)
{
	m_param[num].buffer_type = MYSQL_TYPE_VARCHAR;
	m_param[num].buffer = val;
	m_param[num].buffer_length = strlen(val);
}

void MysqlPrepare::BindVarChar(unsigned char num, char *val, unsigned int length)
{
	m_param[num].buffer_type = MYSQL_TYPE_VARCHAR;
	m_param[num].buffer = val;
	m_param[num].buffer_length = length;
}

void MysqlPrepare::BindText(unsigned char num, char *val)
{
	m_param[num].buffer_type = MYSQL_TYPE_BLOB;
	m_param[num].buffer = val;
	m_param[num].buffer_length = strlen(val);
}

void MysqlPrepare::BindText(unsigned char num, char *val, unsigned int length)
{
	m_param[num].buffer_type = MYSQL_TYPE_BLOB;
	m_param[num].buffer = val;
	m_param[num].buffer_length = length;
}