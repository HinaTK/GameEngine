
#include <stdio.h>
#include "base.h"
#include "lib/include/base/function.h"

MysqlBase::MysqlBase(const char *ip, const char *user, const char *password, const char *db, unsigned short port)
{
	strcpy(m_host, ip);
	strcpy(m_user, user);
	strcpy(m_passwd, password);
	strcpy(m_db, db);
	m_port = port;
	if (!Connect())
	{
		Close();
	}
}

MysqlBase::~MysqlBase()
{
	Close();
}

bool MysqlBase::Connect()
{
	m_mysql = mysql_init(NULL);
	if (m_mysql == NULL)
	{
		Function::Info("mysql_init error, maybe the memory is not enough");
		return false;
	}

	char arg = 1;
	mysql_options(m_mysql, MYSQL_OPT_RECONNECT, &arg);
	if (mysql_real_connect(m_mysql, m_host, m_user, m_passwd, m_db, m_port, 0, 0) == NULL)
	{
		Function::Info("mysql_real_connect error: %s", mysql_error(m_mysql));
		return false;
	}
	return true;
}

bool MysqlBase::Reconnect()
{
	Close();
	return Connect();
}

void MysqlBase::Close()
{
	if (m_mysql != NULL)
	{
		mysql_close(m_mysql);
		m_mysql = NULL;
	}
}