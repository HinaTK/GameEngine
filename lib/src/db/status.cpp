
#include <stdio.h>
#include "status.h"

MysqlStatus::MysqlStatus(const char *ip, const char *user, const char *password, const char *db)
{
	m_mysql = mysql_init(NULL);
	if (m_mysql == NULL)
	{
		printf("mysql_init error, maybe the memory is not enough\n");
		return;
	}

	if (mysql_real_connect(m_mysql, ip, user, password, db, 0, 0, 0) == NULL)
	{
		printf("mysql_real_connect error ...\n");
		return;
	}
}

MysqlStatus::~MysqlStatus()
{
	if (m_mysql != NULL)
	{
		mysql_close(m_mysql);
		m_mysql = NULL;
	}
}

