
#ifndef TABLE_BASE_H
#define TABLE_BASE_H

#ifdef WIN32
#include <winsock2.h>
#include "include/mysql.h"
#endif
#ifdef __unix
#include <mysql/mysql.h>
#endif
#include <string>

class TableBase
{
public:
	TableBase(unsigned short table_type, std::string table_name, MYSQL_STMT* stmt);
	~TableBase(){};

	enum MysqlOperation
	{
		SELECT_OPER,
		UPDATE_OPER,
		DELETE_OPER,
		MAX_OPERATION
	};

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

	virtual std::string *	FieldsName() = 0;

	virtual unsigned int	MaxField() = 0;

	virtual MYSQL_BIND *	GetParam() = 0;

	void					Init();

	bool					Insert();

	bool					Select();

	bool					Update();

	bool					Delete();

	void	SetCondition(std::string field, int val, unsigned int relation, unsigned int oper, bool is_end = false, unsigned int connect = AND);

	void	SetCondition(std::string field, std::string val, unsigned int relation, unsigned int oper, bool is_end = false, unsigned int connect = AND);

protected:
	unsigned short	m_table_type;
	std::string		m_table_name;
	MYSQL_STMT*		m_stmt;
private:
	std::string		m_insert_base;
	std::string		m_select_base;
	std::string		m_update_base;
	std::string		m_delete_base;
	std::string		m_condition[MAX_OPERATION];
};


#define VAR_DEFINE(class, val)\
class m_##val;

#define FIELD(val)\
	m_##val

#define PARAM_BIND(field, type)\
	m_param[field].buffer_type = type; \
	m_param[field].buffer = &FIELD(field); \
	m_param[field].length = 0;

#endif