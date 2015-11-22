
#ifndef TB_LOGIN_H
#define TB_LOGIN_H

#include "database/tablebase.h"
#include "lib/include/cache/datacache.h"

class TB_Login : public TableBase
{
public:
	TB_Login(unsigned short type, std::string table_name, MYSQL_STMT* stmt);
	virtual ~TB_Login(){}

	enum Fields
	{
		id,
		account,
		password,
		name,
		last_time,		// 最后调用时间
		MAX_FIELD
	};

	VAR_DEFINE(unsigned int, id );
	VAR_DEFINE(unsigned int, account);
	VAR_DEFINE(unsigned int, password);
	STR_DEFINE(name);
	VAR_DEFINE(unsigned int, last_time);


// protected:
// 	bool			BindResult();
};

#endif