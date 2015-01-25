#ifndef GAMEMYSQL_H
#define GAMEMYSQL_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "database.h"


/*
 一个对象操作一个表
*/
//mysql_library_init
//mysql_library_end(),不使用可能导致内存泄露
//还需要将字符串转化成整型

struct MysqlCell
{
    unsigned int fields;
    unsigned int rows;
};

#define MYSQLERROR -1   //

/*
 *数据库事务的作用之一是：在多次操作数据库一次提交（commit），这样可以提高效率
 */

struct Cell
{
    std::string fieldname;
    union
    {
        int value;
    };
};


//template <class T>
class GameMysql:public DataBase
{ 
public:
    enum GDATATYPE
    {
        FIELDS,             //获得字段名
        ROWS,               //获得数据行
        UPDATEDATA,         //更新数据
        DELETEDATA          //删除数据
    };

	enum GSQL
	{
		GDELETE,
		GUPDATE,
        GINSERT,
        GSELECT,
		MAX_SQL
	};




    typedef struct gamemysql_allrows
    {
        unsigned int length;
		std::vector<MYSQL_ROW> row;
    }ALLROWS;

    GameMysql(std::string tablename);
    ~GameMysql();
    void * Query(char *sql,unsigned int type,MysqlCell *cell=NULL);
    bool Insert();
    bool Update();
    bool Delete();

    void Transaction(); //事务开始
    void Commit();      //事务提交
    void RollBack();    //事务回滚
	void Execute();

    MYSQL_FIELD * Find(unsigned int &len);
    unsigned int Find(MYSQL_FIELD **fields);
    unsigned int Find(ALLROWS &row);

    unsigned int Count();
	
    void SetDeleteCondition(std::string field,int val, unsigned int relation,bool isend = true, unsigned int connecttype = GameMysql::AND);
    void SetDeleteCondition(std::string field,std::string val, unsigned int relation,bool isend = true, unsigned int connecttype = GameMysql::AND);

    void SetUpdateCondition(std::string field,int val, unsigned int relation,bool isend = true, unsigned int connecttype = GameMysql::AND);
    void SetUpdateCondition(std::string field,std::string val, unsigned int relation,bool isend = true, unsigned int connecttype = GameMysql::AND);


    void SetSelectCondition(std::string field,int val,unsigned int relation,bool isend = true, unsigned int connecttype = GameMysql::AND);
    void SetSelectCondition(std::string field,std::string val,unsigned int relation,bool isend = true, unsigned int connecttype = GameMysql::AND);

    void SetConditionEnd();

    void SetUpdateVal(std::string field, int val,bool isend = true);
    void SetUpdateVal(std::string field, std::string val,bool isend = true);

    void SetInsertVal(std::string field, int val,bool isend = true);
    void SetInsertVal(std::string field, std::string val,bool isend = true);

    void SetFindVal(std::string field, bool isend = true);
	void SetFindVal(std::string field[]);

    

    static void ClearAllRows(ALLROWS &rows);
     MYSQL *GetHandle(){ return DataBase::Instance().GetHandle(); }
private:

	std::string m_sql[MAX_SQL];

	std::string m_condition[MAX_SQL];

	std::string m_insertkey;
	std::string m_insertval;

    //std::string m_updateval;
    std::string m_updateval;
    std::string m_findval;

    //MYSQL  m_mysql;         //一定要将这个放在类的声明里面，不然的话会出错
    //MYSQL *m_db_handle ;
    MYSQL_RES *m_data_res;

    static GameMysql *m_game_mysql;
	std::string m_table_name;
};

//extern MYSQL *g_db_handle;

#endif // MYSQL_H

