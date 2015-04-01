
#ifndef DATABASE_H
#define DATABASE_H

#ifdef WIN32
#include <winsock2.h>
#include "include/mysql.h"
#endif
#ifdef __unix
#include <mysql/mysql.h>
#endif
#include <string>

#include "common/datastructure/gamelist.h"

// http://dev.mysql.com/downloads/mysql/

class DataBase
{
public:
	enum CONNECT
	{
		AND,
		OR,
		MAX_CONNECT
	};
	
	enum RELATION
	{
		GT,             //大于
		EQ,             //等于
		LT,             //小于
		GTE,			//大于等于
		LTE,			//小于等于
		NE,				//不等于
		MAX_RELATION
	};
	
	enum ERRORTYPE
	{
		RELATION_OVER,
		CONNECT_OVER,
		OPERATION_OVER,
		MAX_ERROR
	};

public:
    ~DataBase();
    static DataBase &Instance()
    {
        static DataBase instance;
        return instance;
    }

	struct MysqlConnect
	{
		MYSQL		*mysql;
		MYSQL_STMT	*stmt;
	};

    bool		Init(char *server, char *dbname, char *username, char *password);
	void		ErrorInfo(int error);
	bool		GetMysqlConnect(MysqlConnect &mc);
 //   MYSQL_STMT	*GetStmt(){return m_stmt;}


protected:
	DataBase(){}

private:
	game::List<MysqlConnect> m_connect_pool;
};

#endif
