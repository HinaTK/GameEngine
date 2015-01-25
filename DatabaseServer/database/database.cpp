#include "database.h"
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
	m_db_handle = mysql_real_connect(mysql,server,username,password,dbname,0,0,0);

	if (m_db_handle == NULL)
	{
		printf("%s\n",mysql_error(mysql));
		printf("init database error\n");
		return false;
	}
	m_stmt = mysql_stmt_init(mysql);
	if (m_stmt == NULL)
	{
		printf("%s\n",mysql_error(mysql));
		printf("init database error\n");
		return false;
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