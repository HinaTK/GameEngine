
#ifdef WIN32
#include <winsock2.h>
#include "include/mysql.h"
#endif
#ifdef __unix
#include <mysql/mysql.h>
#endif
#include "gamemysql.h"
//#include "../tinyxml/typeconversion.h"

static const char *relationType[] = { ">" , "=" , "<" , ">=" , "<=" , "<>" };
static const char *connectType[]= {" AND "," OR "};
//static MYSQL *GetHandle();


#define CHECKRELATION(r)\
    if (r >= DataBase::MAX_RELATION)\
    {\
        this->ErrorInfo(DataBase::RELATION_OVER);\
        return;\
    }\

#define CHECKCONNECT(c)\
    if (c >= DataBase::MAX_CONNECT)\
    {\
        this->ErrorInfo(DataBase::CONNECT_OVER);\
        return;\
    }\

#define SETTEMP(str)\
    static std::string temp = "";\
    temp = "";\
    if (!isend) temp = str;\

#define HANDLEERROR(re)\
    if (GetHandle() ==NULL)\
    {\
        printf("Mysql Handle is NULL\n");\
        return re;\
    }\


GameMysql::GameMysql(std::string tablename)
    :DataBase()
, m_insertkey("")
, m_insertval("")
, m_table_name(tablename)
{   
	for (int i = 0; i < GameMysql::MAX_SQL; ++i)
	{
		m_sql[i] = "";
		m_condition[i] = "";
	}
	
}

GameMysql::~GameMysql()
{
    mysql_free_result(m_data_res);
}



void * GameMysql::Query(char *sql,unsigned int type,MysqlCell *cell)
{
    if (sql != NULL)
    {
        int query_error = mysql_query(GetHandle(),sql);//查询
        if(query_error != 0)//错误处理
        {
            printf("%s\n",mysql_error(GetHandle()));
            return NULL;
        }
        if (type == UPDATEDATA || type == DELETEDATA)   //当是更新或者是删除数据，那就返回结果1
        {
            int *result = new int;
            *result=(int)mysql_affected_rows(GetHandle());
            return (void *)result;
        }
        if (m_data_res != NULL)
        {
            m_data_res = mysql_store_result(GetHandle());//获取记录
        }
        else
        {
            m_data_res = new MYSQL_RES;
        }
    }
    if(m_data_res != NULL)
    {
        if (cell != NULL)
        {
            cell->fields = mysql_num_fields(m_data_res);
            cell->rows = (int)mysql_num_rows(m_data_res);
        }
        switch(type)
        {
        case FIELDS:
            return mysql_fetch_fields(m_data_res);
        case ROWS:
            return mysql_fetch_row(m_data_res);
        }
    }
    return NULL;
}

bool GameMysql::Insert()
{
    HANDLEERROR(false);
	m_sql[GameMysql::GINSERT] = "INSERT INTO " + m_table_name + "(" + m_insertkey + ") VALUES (" + m_insertval + ")";
    m_insertval = "";
    if (0 != mysql_query(GetHandle(),m_sql[GameMysql::GINSERT].c_str()))
    {
        printf("Mysql Insert Error...\n");
        return false;
    }
    return true;
}

bool GameMysql::Update()
{
    HANDLEERROR(false);
    m_sql[GameMysql::GUPDATE] = "UPDATE " + m_table_name + " SET " + m_updateval + " WHERE " + m_condition[GameMysql::GUPDATE] ;
    m_condition[GameMysql::GUPDATE] = "";
    m_updateval = "";
    if (0 != mysql_query(GetHandle(),m_sql[GameMysql::GUPDATE].c_str()))
    {
        printf("Mysql Update Error...\n");
        return false;
    }
    return true;
}

bool GameMysql::Delete()
{
    HANDLEERROR(false);
    m_sql[GameMysql::GDELETE] = "DELETE FROM " + m_table_name + " WHERE " + m_condition[GameMysql::GDELETE];
    m_condition[GameMysql::GDELETE] = "";
    if (0 != mysql_query(GetHandle(),m_sql[GameMysql::GDELETE].c_str()))
    {
        printf("Mysql Delete Error...\n");
        return false;
    }
    return true;
}


unsigned int GameMysql::Find(MYSQL_FIELD ** fields)
{
     HANDLEERROR(0);
    m_sql[GameMysql::GSELECT] = "SELECT * FROM " + m_table_name + " LIMIT 1";
    static unsigned int len = 0;
    if (0 != mysql_query(GetHandle(),m_sql[GameMysql::GSELECT] .c_str()))
    {
        printf("Mysql Find Fields Error...\n");
        len = 0;
    }
    else
    {
        m_data_res = mysql_store_result(GetHandle());//获取记录
        *fields = mysql_fetch_fields(m_data_res);
        len = mysql_num_fields(m_data_res);
        //mysql_free_result(m_data_res);
    }
    return len;
}

unsigned int  GameMysql::Find(ALLROWS &rows)
{
    HANDLEERROR(0);
    if (m_findval == "") m_findval = "*";

    if (m_condition[GameMysql::GSELECT] == "" )
    {
        m_sql[GameMysql::GSELECT] = "SELECT " + m_findval + " FROM " + m_table_name;
    }
    else
    {
        m_sql[GameMysql::GSELECT] = "SELECT " + m_findval + " FROM " + m_table_name  + " WHERE " + m_condition[GameMysql::GSELECT];
        m_condition[GameMysql::GSELECT] = "";
    }

    static unsigned int field_len = 0;

    if (0 != mysql_query(GetHandle(),m_sql[GameMysql::GSELECT] .c_str()))
    {
        printf("Mysql Find Rows Error...\n");
        field_len = 0;
        rows.length = 0;
    }
    else
    {
        m_data_res = mysql_store_result(GetHandle());//获取记录
        static MYSQL_ROW row;
        while((row = mysql_fetch_row(m_data_res)) != NULL)
        {
            rows.row.push_back(row);
        }
        field_len = mysql_num_fields(m_data_res);
        rows.length = (int)mysql_num_rows(m_data_res);
    }
    m_findval = "";
    return field_len;
}

unsigned int GameMysql::Count()
{
   HANDLEERROR(0);
    static unsigned int count;
    count = 0;
    m_sql[GameMysql::GSELECT] = "SELECT COUNT(*) AS countunm FROM " + m_table_name + " WHERE " + m_condition[GameMysql::GSELECT];
    if (0 != mysql_query(GetHandle(),m_sql[GameMysql::GSELECT] .c_str()))
    {
        printf("Mysql Count Rows Error...\n");
    }
    else
    {
        m_data_res = mysql_store_result(GetHandle());//获取记录
        static MYSQL_ROW row;
        row = mysql_fetch_row(m_data_res);
        if (row != NULL)
        {
            count = atoi(row[0]);
        }
    }

    return count;
}

void GameMysql::Transaction()
{
    mysql_query(GetHandle(),"START TRANSACTION");
}


void GameMysql::Commit()
{
    mysql_query(GetHandle(),"COMMIT");
}

void GameMysql::RollBack()
{
    mysql_query(GetHandle(),"ROLLBACK");
}



void GameMysql::SetDeleteCondition( std::string field, int val, unsigned int r, bool isend /*= true*/ ,unsigned int c)
{
    CHECKRELATION(r);
    CHECKCONNECT(c);
	SETTEMP(connectType[c]);
    static char str_val[32];
	sprintf(str_val,"%d",val);

	m_condition[GameMysql::GDELETE] =  m_condition[GameMysql::GDELETE] + field + relationType[r] +str_val + temp;

}

void GameMysql::SetDeleteCondition( std::string field, std::string val, unsigned int r, bool isend /*= true*/ ,unsigned int c)
{
    CHECKRELATION(r);
    CHECKCONNECT(c);
    SETTEMP(connectType[c]);

    m_condition[GameMysql::GDELETE] =  m_condition[GameMysql::GDELETE] + field + relationType[r] + "'" + val + "'" + temp;

}

void GameMysql::SetUpdateCondition( std::string field, int val, unsigned int r, bool isend /*= true*/,unsigned int c)
{
    CHECKRELATION(r);
    CHECKCONNECT(c);
    SETTEMP(connectType[c]);

    static char str_val[32];
    sprintf(str_val,"%d",val);

    m_condition[GameMysql::GUPDATE] =  m_condition[GameMysql::GUPDATE] + field + relationType[r] +str_val + temp;
}

void GameMysql::SetUpdateCondition( std::string field, std::string val, unsigned int r, bool isend /*= true*/ ,unsigned int c)
{
    CHECKRELATION(r);
    CHECKCONNECT(c);
    SETTEMP(connectType[c]);

    m_condition[GameMysql::GUPDATE] =  m_condition[GameMysql::GUPDATE] + field + relationType[r] + "'" + val + "'" + temp;
}


void GameMysql::SetSelectCondition( std::string field, int val, unsigned int r, bool isend /*= true*/ ,unsigned int c)
{
    CHECKRELATION(r);
    CHECKCONNECT(c);
    SETTEMP(connectType[c]);
    static char str_val[32];
    sprintf(str_val,"%d",val);

    m_condition[GameMysql::GSELECT] =  m_condition[GameMysql::GSELECT] + field + relationType[r] +str_val + temp;
}

void GameMysql::SetSelectCondition( std::string field, std::string val, unsigned int r, bool isend /*= true*/ ,unsigned int c)
{
    CHECKRELATION(r);
    CHECKCONNECT(c);
    SETTEMP(connectType[c]);

    m_condition[GameMysql::GSELECT] =  m_condition[GameMysql::GSELECT] + field + relationType[r] + "'" + val + "'" + temp;
}

void GameMysql::SetConditionEnd()
{

}

void GameMysql::Execute()
{
    if (m_sql[GameMysql::GDELETE] != "")
	{
        Delete();
	}
    if (m_sql[GameMysql::GUPDATE] != "")
	{
       Update();
	}
    if (m_sql[GameMysql::GINSERT]!= "")
	{
        Insert();
	}
	//查找（select）可能有点特殊，这里再研究,这里还要注意的是读取多条数据，具体可参考排行榜
	//上面这样做是为了延迟删除，但是查询不能延迟删除
	//但是这里还是可以写，当判断是查询的时候立刻将上面的删除，更新，插入，保持数据一致
}

void GameMysql::SetInsertVal( std::string field, std::string val ,bool isend /*= true*/)
{
    SETTEMP(",");
        m_insertkey = m_insertkey + field + temp;
        m_insertval = m_insertval + "'" + val + "'" + temp;
}

void GameMysql::SetInsertVal( std::string field, int val ,bool isend /*= true*/)
{
    SETTEMP(",");
	static char str_val[32];
	sprintf(str_val,"%d",val);
    m_insertkey = m_insertkey + field + temp;
    m_insertval = m_insertval + str_val + temp;
}

void GameMysql::SetUpdateVal( std::string field, int val,bool isend /*= true*/)
{
    SETTEMP(",");
	static char str_val[32];
	sprintf(str_val,"%d",val);
    m_updateval =  m_updateval +  field  + "=" + str_val + temp ;
}

void GameMysql::SetUpdateVal(std::string field, std::string val,bool isend /*= true*/)
{
    SETTEMP(",");
    m_updateval =  m_updateval + field  + "='" + val  + "'" + temp;
}

void GameMysql::SetFindVal(std::string field, bool isend)
{
    SETTEMP(",");
    m_findval = m_findval + field + temp;
}


void GameMysql::ClearAllRows(GameMysql::ALLROWS &rows)
{
    if (rows.row.size() > 0)
    {
        rows.row.clear();
    }
}

