
#include <stdio.h>
#include "prepare.h"
#include "handler.h"
#include "lib/include/base/function.h"

MysqlPrepare::MysqlPrepare(MysqlHandler *handler, unsigned char num)
: m_handler(handler)
, m_param(NULL)
, m_stmt(NULL)
{
	if (num > 0)
	{
		m_param = new MYSQL_BIND[num];
		memset(m_param, 0, sizeof(MYSQL_BIND)* num);
	}
}

MysqlPrepare::~MysqlPrepare()
{
	if (m_param != NULL)
	{
		delete []m_param;
		m_param = NULL;
	}

	Close();
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
