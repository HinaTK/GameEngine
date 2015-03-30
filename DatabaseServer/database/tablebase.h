
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
#include <vector>

/*
	需要解决问题：多线程读写
*/
class TableBase
{
public:
	TableBase(unsigned int max_field, unsigned short table_type, std::string table_name, MYSQL_STMT* stmt);
	virtual ~TableBase();

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

	struct StrInfo
	{
		unsigned int	length;
		char *			data;
	};

	struct StrField
	{
		unsigned int	field;
		unsigned int	length;
	};

	void					Init();

	// 目前只支持插入一条数据，插入多条待写(原公司代码没有插入多条)
	bool					Insert();

	bool					Select();

	bool					Update();

	bool					Delete();

	void	SetCondition(std::string field, int val, unsigned int relation, unsigned int oper, bool is_end = false, unsigned int connect = AND);

	void	SetCondition(std::string field, std::string val, unsigned int relation, unsigned int oper, bool is_end = false, unsigned int connect = AND);

	unsigned int			MaxField(){ return m_max_field; };
	bool					HasResult();
	void					ResetBufferLength();
	void					SetBufferLength(unsigned int field, unsigned int length);

protected:

private:
	typedef std::vector<StrField> STR_FIELD;

protected:
	unsigned short	m_table_type;
	std::string		m_table_name;
	std::string*	m_field_name;
	MYSQL_STMT*		m_stmt;
	MYSQL_BIND*		m_result;
	MYSQL_BIND*		m_param;
	
	STR_FIELD		m_str_field;

private:
	std::string		m_insert_base;
	std::string		m_select_base;
	std::string		m_update_base;
	std::string		m_delete_base;
	std::string		m_condition[MAX_OPERATION];
	unsigned int	m_max_field;
};


#define VAR_DEFINE(class, val)\
	class m_##val;

#define STR_DEFINE(val)\
	StrInfo m_##val;

#define FIELD(val)\
	m_##val

#define PARAM_BIND(field, type)\
	m_param[field].buffer_type = type; \
	m_param[field].buffer = &FIELD(field); \
	m_param[field].length = 0;

#define PARAM_BIND_STR(_field, type, _length)\
	m_param[_field].buffer_type = type; \
	FIELD(_field).length = _length; \
	FIELD(_field).data = (char *)MemoryVL::Instance().Malloc(_length); \
	m_param[_field].buffer = FIELD(_field).data; \
	m_param[_field].buffer_length = FIELD(_field).length; \
	m_param[_field].length = 0; \
	StrField sf; \
	sf.field = _field; \
	sf.length = _length;\
	m_str_field.push_back(sf);

#define BIND_RESULT_BEGIN()\
	MYSQL_RES *metadata = mysql_stmt_result_metadata(m_stmt);\
	if (NULL == metadata)\
	{\
		return false;\
	}\
	unsigned int field_num = mysql_num_fields(metadata);\
	MYSQL_FIELD* fields = mysql_fetch_fields(metadata);\
	if (fields == NULL)\
	{\
		return false;\
	}

#define BIND_RESULT_END()\
	if (0 != mysql_stmt_bind_result(m_stmt, GetParam()))\
	{\
		return false;\
	}\
	return true;



#endif