
#ifndef TABLE_DEFINE_H
#define TABLE_DEFINE_H

#include "database/tablebase.h"
#include "lib/include/cache/datacache.h"

class Login : public TableBase
{
public:
	Login(unsigned short type, std::string table_name, MYSQL_STMT* stmt);
	virtual ~Login(){}

	enum Fields
	{
		server_id,
		origin_pname,
		prefix_pname,
		prefix_rname,
		role_id,		
		create_time_s,
		last_login_ip,
		MAX_FIELD
	};

	VAR_DEFINE(unsigned int, server_id);
	STR_DEFINE(origin_pname);
	STR_DEFINE(prefix_pname);
	STR_DEFINE(prefix_rname);
	VAR_DEFINE(unsigned int, role_id);
	VAR_DEFINE(unsigned int, create_time_s);
	STR_DEFINE(last_login_ip);
};

#endif