
#include "database.h"
#include "table/tb_login.h"
#include "lib/include/tinyxml/tinyxml.h"


DataBase::~DataBase()
{
// 	if (m_stmt != NULL)
// 	{
// 		mysql_stmt_close(m_stmt);
// 	}
// 	if (m_mysql != NULL)
//     {
// 		mysql_close(m_mysql);
//     }
}


bool DataBase::Init( char *server, char *dbname, char *username, char *password )
{
	for (int i = 0; i < 3; ++i)
	{
		MysqlConnect mc;
		mc.mysql = mysql_init(NULL);
		MYSQL *temp = mysql_real_connect(mc.mysql, server, username, password, dbname, 0, 0, 0);
		if (temp == NULL)
		{
			return false;
		}
		mc.stmt = mysql_stmt_init(mc.mysql);
		if (mc.stmt == NULL)
		{
			return false;
		}
		m_connect_pool.PushBack(mc);
	}
	return true;
}



void DataBase::ErrorInfo(int error)
{
	if (error >= DataBase::MAX_ERROR)
	{
		printf("has errors in %d\n",error);
	}
	switch(error)
	{
	case DataBase::RELATION_OVER:
		printf("DataBase : Input relation is over the define\n");
		break;
	case DataBase::CONNECT_OVER:
		printf("DataBase : Input connect is over the define\n");
		break;
	}
}

bool DataBase::GetMysqlConnect(MysqlConnect &mc)
{
	return m_connect_pool.PopFront(mc);
}
