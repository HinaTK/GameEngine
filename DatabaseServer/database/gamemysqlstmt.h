#ifndef GAMEMYSQLSTMT_H
#define GAMEMYSQLSTMT_H

#include "../../common/commonvariable.h"
#include <string>
#include "database.h"

/*
	update delete insert����ʵʱд���ݿ⣬��Ӱ�����ݷ��ؿͻ��ˣ����ұ����ڴ�����ݿ��Զ�ʱ���̡�
	���磺����ڱ�������һ����Ʒ��ֻҪ���ڴ����������Ѿ�ɾ������ʱ���ˣ���ͳһд���ݿ⡣
	����select���У���Ϊ�ͻ����ڵȴ���������Ӱ������������
*/

class GameMysqlStmt : public DataBase
{
public:
	GameMysqlStmt(std::string tablename);
	~GameMysqlStmt();

	enum MysqlOperation
	{
		SELECT_OPER,
		UPDATE_OPER,
		DELETE_OPER,
		MAX_OPERATION
	};

    MYSQL_STMT *			GetStmt(){ return DataBase::Instance().GetStmt();}

	virtual std::string *	GetFields() = 0;

	virtual UInt32			GetMaxField() = 0;

	virtual MYSQL_BIND *	GetParam() = 0;

	virtual bool			Insert();

//	virtual bool			Insert(MYSQL_BIND ** param, UInt32 col);			// ���ڶ��в���param[i * j]

	virtual bool			Select();

	virtual bool			HasResult();

	virtual bool			Update();

	virtual bool			Delete();

	virtual	void			SetSelectField(std::string field, bool is_end = false);

	virtual void	SetCondition(std::string field, int val,			UInt32 relation, UInt32 oper, bool is_end = false, UInt32 connect = DataBase::AND);

	virtual void	SetCondition(std::string field, std::string val,	UInt32 relation, UInt32 oper, bool is_end = false, UInt32 connect = DataBase::AND);


protected:
	std::string m_table_name;
private:
	std::string		m_select_fields;
	std::string		m_condition[MAX_OPERATION];
	//std::string		m_update_fields;
	std::string		m_update_condition;
	//MYSQL_STMT *m_stmt;
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
