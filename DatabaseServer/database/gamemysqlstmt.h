#ifndef GAMEMYSQLSTMT_H
#define GAMEMYSQLSTMT_H

#include "../../common/commonvariable.h"
#include <string>
#include "database.h"

/*
	update delete insert可以实时写数据库，不影响数据返回客户端；而且保存内存的数据可以定时存盘。
	例如：玩家在背包丢弃一个物品，只要在内存数组里标记已经删除，到时间了，再统一写数据库。
	但是select不行，因为客户端在等待，这样会影响在线人数。
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

//	virtual bool			Insert(MYSQL_BIND ** param, UInt32 col);			// 用于多行插入param[i * j]

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
