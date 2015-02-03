
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

// http://dev.mysql.com/downloads/mysql/
//#pragma comment(lib,"../lib/libmysql.lib")

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
		GT,             //����
		EQ,             //����
		LT,             //С��
		GTE,			//���ڵ���
		LTE,			//С�ڵ���
		NE,				//������
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

    bool Init(char *server, char *dbname, char *username, char *password);
	void ErrorInfo(int error);
    MYSQL *GetHandle(){return m_db_handle;}
    MYSQL_STMT *GetStmt(){return m_stmt;}
protected:
	DataBase(){}

    
private:
    MYSQL *m_db_handle;
    MYSQL_STMT *m_stmt;
};

#endif
