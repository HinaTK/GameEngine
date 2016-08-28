
#include "preparestatic.h"
#include "handler.h"
#include "lib/include/base/function.h"

MysqlPrepareStatic::MysqlPrepareStatic(MysqlHandler *handler, unsigned char num, const char *sql, unsigned short sql_len /*= 0*/)
: MysqlPrepare(handler, num)
{
	sql_len == 0 ? m_sql_len = strlen(sql) : m_sql_len = sql_len;
	m_sql = new char[m_sql_len + 1];
	memcpy(m_sql, sql, m_sql_len);
	m_sql[m_sql_len] = 0;
}

bool MysqlPrepareStatic::Init()
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
		unsigned int err = mysql_stmt_errno(m_stmt);
		if (err == CR_SERVER_LOST || err == CR_SERVER_GONE_ERROR)
		{
			if (mysql_ping(m_handler->GetMysql()) == 0)
			{
				if (mysql_stmt_prepare(m_stmt, m_sql, m_sql_len) == 0)
				{
					return true;
				}
			}
		}

		Function::Info("mysql_stmt_prepare error %s", m_sql);
		Function::Info("%s", mysql_stmt_error(m_stmt));
		return false;
	}

	return true;
}

bool MysqlPrepareStatic::Execute(unsigned short reconnect /*= true*/)
{
	if (mysql_stmt_bind_param(m_stmt, m_param) != 0)
	{
		unsigned int err = mysql_stmt_errno(m_stmt);
		if (err == CR_NO_PREPARE_STMT && (reconnect & RE_BIND) && Init())
		{
			return Execute(reconnect ^ RE_BIND);
		}
		Function::Info("mysql_stmt_bind_param error %d %s", err, mysql_stmt_error(m_stmt));
		return false;
	}

	if (mysql_stmt_execute(m_stmt) != 0)
	{
		unsigned int err = mysql_stmt_errno(m_stmt);
		if ((err == CR_SERVER_LOST || err == CR_SERVER_GONE_ERROR) && (reconnect & RE_EXECUTE) && Init())
		{
			return Execute(reconnect ^ RE_EXECUTE);
		}

		Function::Info("mysql_stmt_execute error %d %s", err, mysql_stmt_error(m_stmt));
		return false;
	}
	return true;
}

