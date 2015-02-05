
#ifndef TB_LOGIN_H
#define TB_LOGIN_H

#include "database/gamemysqlstmt.h"
#include "cache/datacache.h"

class TB_Login : public GameMysqlStmt
{
public:
	~TB_Login()
	{
		//m_cache.m_data.FreePointer();
	};

	static TB_Login & Instance()
	{
		static TB_Login login("login");
		return login;
	}
	enum Fields
	{
		ID,
		ACCOUNT,
		PASSWORD,
		NAME,
		LAST_TIME,		// 最后调用时间
		MAX_FIELD
	};

	VAR_DEFINE(UInt32, ID );
	VAR_DEFINE(UInt32, ACCOUNT );
	VAR_DEFINE(UInt32, PASSWORD);
	VAR_DEFINE(char* , NAME);
	VAR_DEFINE(UInt32, LAST_TIME);

	// 抽象函数写成宏，方便编写
	std::string *	GetFields();

	UInt32			GetMaxField(){return MAX_FIELD;}

	MYSQL_BIND *	GetParam(){return m_param;}

	DataCache *		GetCache(){return &m_cache;}

private:
	TB_Login(std::string table_name);

private:
	DataCache	m_cache;
	MYSQL_BIND	m_param[MAX_FIELD];
	std::string m_field_name[MAX_FIELD];
};

#endif