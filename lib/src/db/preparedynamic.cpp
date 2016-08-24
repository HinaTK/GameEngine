
#include "preparedynamic.h"
#include "handler.h"
#include "lib/include/base/function.h"

MysqlPrepareDynamic::MysqlPrepareDynamic(MysqlHandler *handler, unsigned char num)
: MysqlPrepare(handler, num)
{

}

bool MysqlPrepareDynamic::Execute(const char *sql, unsigned short sql_len)
{
	m_stmt = mysql_stmt_init(m_handler->GetMysql());
	if (m_stmt == NULL)
	{
		// A pointer to a MYSQL_STMT structure in case of success. NULL if out of memory.
		Function::Info("mysql_stmt_init error %d %s", mysql_stmt_errno(m_stmt), sql);
		return false;
	}

	if (mysql_stmt_prepare(m_stmt, sql, sql_len) != 0)
	{
		Function::Info("mysql_stmt_prepare error %s", sql);
		Function::Info("%d %s", mysql_stmt_errno(m_stmt), mysql_stmt_error(m_stmt));
		return false;
	}

	if (mysql_stmt_bind_param(m_stmt, m_param) != 0)
	{
		Function::Info("mysql_stmt_bind_param error %d %s", mysql_stmt_errno(m_stmt), mysql_stmt_error(m_stmt));
		return false;
	}

	if (mysql_stmt_execute(m_stmt) != 0)
	{

		Function::Info("mysql_stmt_execute error %d %s", mysql_stmt_errno(m_stmt), mysql_stmt_error(m_stmt));
		return false;
	}
	return true;
}

