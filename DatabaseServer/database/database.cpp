
#include "database.h"
#include "table/tb_login.h"
#include "libtinyxml.h"


DataBase::~DataBase()
{
	if (m_stmt != NULL)
	{
		mysql_stmt_close(m_stmt);
	}
    if (m_db_handle != NULL)
    {
        mysql_close(m_db_handle);
    }
}


bool DataBase::Init( char *server, char *dbname, char *username, char *password )
{
	MYSQL *mysql;
	mysql = mysql_init(NULL);
	m_db_handle = mysql_real_connect(mysql, server, username, password, dbname,0,0,0);
	do 
	{
		if (m_db_handle == NULL)
		{
			break;
		}
		m_stmt = mysql_stmt_init(mysql);
		if (m_stmt == NULL)
		{
			break;
		}
		TB_Login test(0, "login", m_stmt);
		test.Init();
		test.m_ID = 123;
		test.m_ACCOUNT = 456;
		test.Insert();

		return true;
	} while (false);
	
	printf("%s\n", mysql_error(mysql));
	printf("init database error\n");
	return false;
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