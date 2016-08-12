
#include <stdio.h>
#include "handler.h"
#include "lib/include/base/function.h"

MysqlHandler::MysqlHandler(const char *ip, const char *user, const char *password, const char *db, unsigned short port)
: m_1_pool(1, 8)
, m_2_pool(2, 2)
, m_4_pool(4, 4)
, m_8_pool(8, 2)
{
	strcpy(m_host, ip);
	strcpy(m_user, user);
	strcpy(m_passwd, password);
	strcpy(m_db, db);
	m_port = port;
	Connect();
}

MysqlHandler::~MysqlHandler()
{
	Close();
}

bool MysqlHandler::Connect()
{
	m_mysql = mysql_init(NULL);
	if (m_mysql == NULL)
	{
		Function::Info("mysql_init error, maybe the memory is not enough");
		return false;
	}

	if (mysql_real_connect(m_mysql, m_host, m_user, m_passwd, m_db, m_port, 0, 0) == NULL)
	{
		Function::Info("mysql_real_connect error ...");
		return false;
	}
	return true;
}

bool MysqlHandler::Reconnect()
{
	Close();
	return Connect();
}

void MysqlHandler::Close()
{
	if (m_mysql != NULL)
	{
		mysql_close(m_mysql);
		m_mysql = NULL;
	}
}