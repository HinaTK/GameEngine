
#include <stdio.h>
#include "prepare.h"


MysqlPrepare::MysqlPrepare(MYSQL *mysql, unsigned char num, char *sql, unsigned short sql_len)
: m_param(new MYSQL_BIND[num])
{
	m_stmt = mysql_stmt_init(mysql);
	if (m_stmt == NULL)
	{
		// A pointer to a MYSQL_STMT structure in case of success. NULL if out of memory.
		printf("mysql_stmt_init error %s \n", sql);
		return;
	}
	
	if (mysql_stmt_prepare(m_stmt, sql, sql_len) != 0)
	{
		printf("mysql_stmt_prepare error %s \n", sql);
		printf("%s\n", mysql_stmt_error(m_stmt));
		return;
	}

	memset(m_param, 0, sizeof(MYSQL_BIND)* num);
}

MysqlPrepare::~MysqlPrepare()
{
	if (m_param != NULL)
	{
		delete m_param;
		m_param = NULL;
	}

	if (m_stmt != NULL)
	{
		mysql_stmt_close(m_stmt);
		m_stmt = NULL;
	}
}


void MysqlPrepare::BindTinyInt(unsigned char num, char val)
{
	m_param[num].buffer_type = MYSQL_TYPE_TINY;
	m_param[num].buffer = &val;
}

void MysqlPrepare::BindSmallInt(unsigned char num, short val)
{
	m_param[num].buffer_type = MYSQL_TYPE_SHORT;
	m_param[num].buffer = &val;
}

void MysqlPrepare::BindInt(unsigned char num, int val)
{
	m_param[num].buffer_type = MYSQL_TYPE_LONG;
	m_param[num].buffer = &val;
	//m_param[num].length = 0;
}

void MysqlPrepare::BindLong(unsigned char num, long long val)
{
	m_param[num].buffer_type = MYSQL_TYPE_LONGLONG;
	m_param[num].buffer = &val;
}

void MysqlPrepare::BindFloat(unsigned char num, float val)
{
	m_param[num].buffer_type = MYSQL_TYPE_FLOAT;
	m_param[num].buffer = &val;
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
	m_param[num].buffer_type = MYSQL_TYPE_VAR_STRING;
	m_param[num].buffer = val;
	m_param[num].buffer_length = strlen(val);
}

void MysqlPrepare::BindText(unsigned char num, char *val, unsigned int length)
{
	m_param[num].buffer_type = MYSQL_TYPE_VAR_STRING;
	m_param[num].buffer = val;
	m_param[num].buffer_length = length;
}

bool MysqlPrepare::Execute()
{
	if (mysql_stmt_bind_param(m_stmt, m_param) != 0)
	{
		printf("mysql_stmt_bind_param error %s \n", mysql_stmt_error(m_stmt));
		return false;
	}
	if (mysql_stmt_execute(m_stmt) != 0)
	{
		printf("mysql_stmt_execute error %s \n", mysql_stmt_error(m_stmt));
		return false;
	}
	return true;
}

