
#include <stdio.h>
#include "handler.h"
#include "lib/include/base/function.h"

MysqlHandler::MysqlHandler(const char *ip, const char *user, const char *password, const char *db, unsigned short port)
: m_1_pool(1, 8)
, m_2_pool(2, 2)
, m_4_pool(4, 4)
, m_8_pool(8, 2)
{
	m_mysql = mysql_init(NULL);
	if (m_mysql == NULL)
	{
		Function::Info("mysql_init error, maybe the memory is not enough");
		return;
	}

	if (mysql_real_connect(m_mysql, ip, user, password, db, port, 0, 0) == NULL)
	{
		Function::Info("mysql_real_connect error ...");
		return;
	}

// 	char val = 1;
// 	mysql_options(m_mysql, MYSQL_OPT_RECONNECT, &val);
}

MysqlHandler::~MysqlHandler()
{
	if (m_mysql != NULL)
	{
		mysql_close(m_mysql);
		m_mysql = NULL;
	}
}

