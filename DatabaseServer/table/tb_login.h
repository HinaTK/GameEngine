
#ifndef TB_LOGIN_H
#define TB_LOGIN_H

#include "database/tablebase.h"
#include "cache/datacache.h"

class TB_Login : public TableBase
{
public:
	TB_Login(unsigned short type, std::string table_name, MYSQL_STMT* stmt);
	~TB_Login()
	{
	};

	enum Fields
	{
		ID,
		ACCOUNT,
		PASSWORD,
		NAME,
		LAST_TIME,		// 最后调用时间
		MAX_FIELD
	};

	VAR_DEFINE(unsigned int, ID );
	VAR_DEFINE(unsigned int, ACCOUNT);
	VAR_DEFINE(unsigned int, PASSWORD);
	// VAR_DEFINE(char* , NAME);
	STR_DEFINE(NAME);
	VAR_DEFINE(unsigned int, LAST_TIME);

	// 抽象函数写成宏，方便编写
	std::string *	FieldsName(){ return m_field_name; }

	unsigned int	MaxField(){ return MAX_FIELD; }

	MYSQL_BIND *	GetParam(){return m_param;}

	bool			BindResult();

	bool			HasResult();

protected:
	void			BindParam();

private:
	MYSQL_BIND	m_param[MAX_FIELD];
	std::string m_field_name[MAX_FIELD];
};

#endif