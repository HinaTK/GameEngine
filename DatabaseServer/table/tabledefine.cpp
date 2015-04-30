
#include <string.h>
#include "tabledefine.h"
#include "lib/include/common/memoryvl.h"

Login::Login(unsigned short type, std::string table_name, MYSQL_STMT* stmt)
: TableBase(MAX_FIELD, type, table_name, stmt)
{
	memset(m_param, 0, sizeof(m_param));
	PARAM_BIND(server_id, MYSQL_TYPE_LONG);
	PARAM_BIND_STR(origin_pname, MYSQL_TYPE_VAR_STRING, 64);
	PARAM_BIND_STR(prefix_pname, MYSQL_TYPE_VAR_STRING, 64);
	PARAM_BIND_STR(prefix_rname, MYSQL_TYPE_VAR_STRING, 32);
	PARAM_BIND(role_id, MYSQL_TYPE_LONG);
	PARAM_BIND(create_time_s, MYSQL_TYPE_LONG);
	PARAM_BIND_STR(last_login_ip, MYSQL_TYPE_VAR_STRING, 32);

	m_field_name[server_id]		= "id";
	m_field_name[origin_pname]	= "origin_pname";
	m_field_name[prefix_pname]	= "prefix_pname";
	m_field_name[prefix_rname]	= "prefix_rname";
	m_field_name[role_id]		= "role_id";
	m_field_name[create_time_s] = "create_time_s";
	m_field_name[last_login_ip] = "last_login_ip";
}

