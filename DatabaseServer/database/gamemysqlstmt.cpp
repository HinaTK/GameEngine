#include "gamemysqlstmt.h"
#include <stdio.h>

static const char *relationType[] = { ">" , "=" , "<" , ">=" , "<=" , "<>" };
static const char *connectType[]= {" AND "," OR "};

#define SETSYMBOL(str)\
	static std::string symbol = "";\
	symbol = "";\
	if (!is_end) symbol = str;\

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

#define CHECKOPERATION(o)\
	if (o >= GameMysqlStmt::MAX_OPERATION)\
	{\
		this->ErrorInfo(DataBase::OPERATION_OVER);\
		return;\
	}\


GameMysqlStmt::GameMysqlStmt(std::string tablename)
 :DataBase()
 , m_select_fields("*")
 , m_update_condition("")
 , m_table_name(tablename)
{
    //m_tablename = tablename;
	m_condition[SELECT_OPER] = "";
	m_condition[UPDATE_OPER] = "";
}

GameMysqlStmt::~GameMysqlStmt()
{
	
}

/*
	插入多行
	INSERT INTO m_table_name (field1,field2,...) VALUES (?,?,...),(?,?,...)...
*/

bool GameMysqlStmt::Insert()
{
	std::string insertSql("INSERT INTO " + m_table_name + " (");
	static std::string *fields = GetFields();
	int maxField = GetMaxField();
	std::string val;
	for (int i = 0; i < maxField; ++i)
	{
		insertSql += fields[i] + ",";
		val += "?,";
	}
	insertSql.replace(insertSql.size() - 1, 1, ") VALUES (");
	val.replace(val.size() - 1, 1, ");");
	insertSql += val;
	if ( 0 != mysql_stmt_prepare(DataBase::Instance().GetStmt(), insertSql.c_str(), insertSql.size()) ||
		 0 != mysql_stmt_bind_param(DataBase::Instance().GetStmt(), GetParam()) || 
		 0 != mysql_stmt_execute(DataBase::Instance().GetStmt()) )
	{
		return false;
	}
	return true;
}

/*
	当m_selelct_fields为空是，默认就是查找已经定义的字段；
	这样就不需要每次Select的时候都要构建，其它的操作同理；
	待修改
*/
bool GameMysqlStmt::Select()
{
	std::string selectSql("SELECT " + m_select_fields + " FROM " + m_table_name);
	if (m_condition[SELECT_OPER] != "")
	{
		selectSql = selectSql + " WHERE " + m_condition[SELECT_OPER];
		m_condition[SELECT_OPER] = "";
	}
	
	m_select_fields = "*";
	std::string *fields = GetFields();
    selectSql = "SELECT * FROM " + m_table_name + ";";
	if ( 0 != mysql_stmt_prepare(DataBase::Instance().GetStmt(), selectSql.c_str(), selectSql.size()) ||
		 0 != mysql_stmt_bind_result(DataBase::Instance().GetStmt(), GetParam()) ||
		 0 != mysql_stmt_execute(DataBase::Instance().GetStmt()) ||
		 0 != mysql_stmt_store_result(DataBase::Instance().GetStmt()))
	{
		return false;
	}
	return true;
}

bool GameMysqlStmt::Update()
{
	std::string updateSql("UPDATE " + m_table_name + " SET ");
	static std::string *fields = GetFields();
	int maxField = GetMaxField();
	for (int i = 0; i < maxField; ++i)
	{
		updateSql += fields[i] + "=(?),";
	}
	updateSql.replace(updateSql.size() - 1, 1, "");
	if (m_condition[UPDATE_OPER] == "")
	{
		return false;
	}
	updateSql += " WHERE " + m_condition[UPDATE_OPER] + ";";
	if ( 0 != mysql_stmt_prepare(DataBase::Instance().GetStmt(), updateSql.c_str(), updateSql.size()) ||
		0 != mysql_stmt_bind_param(DataBase::Instance().GetStmt(), GetParam()) || 
		0 != mysql_stmt_execute(DataBase::Instance().GetStmt()) )
	{
		return false;
	}
	return true;
}

bool GameMysqlStmt::Delete()
{
	std::string deleteSql("DELETE FROM " + m_table_name);
	if (m_condition[DELETE_OPER] != "")
	{
		deleteSql += " WHERE " + m_condition[DELETE_OPER];
	}
	deleteSql += ";";
	if ( 0 != mysql_stmt_prepare(DataBase::Instance().GetStmt(), deleteSql.c_str(), deleteSql.size()) ||
		0 != mysql_stmt_bind_param(DataBase::Instance().GetStmt(), GetParam()) || 
		0 != mysql_stmt_execute(DataBase::Instance().GetStmt()) )
	{
		return false;
	}
	return true;
}

bool GameMysqlStmt::HasResult()
{
	if(mysql_stmt_fetch(DataBase::Instance().GetStmt()) == 0)
	{
		return true;
	}
	return false;	
}

void GameMysqlStmt::SetSelectField( std::string field, bool is_end /*= false*/ )
{
	SETSYMBOL(",");
	m_select_fields = m_select_fields + field + symbol;
}

void GameMysqlStmt::SetCondition( std::string field, int val, UInt32 relation, UInt32 oper, bool is_end, UInt32 connect )
{
	CHECKRELATION(relation);
	CHECKCONNECT(connect);
	CHECKOPERATION(oper);
	SETSYMBOL(connectType[connect]);
	static char strVal[32];
	sprintf(strVal,"%d",val);

	m_condition[oper] =  m_condition[oper] + field + relationType[relation] +strVal + symbol;
}

void GameMysqlStmt::SetCondition( std::string field, std::string val, UInt32 relation, UInt32 oper, bool is_end, UInt32 connect )
{

}







