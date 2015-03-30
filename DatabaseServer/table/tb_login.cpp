
#include <string.h>
#include "tb_login.h"
#include "lib/include/common/memoryvl.h"

TB_Login::TB_Login(unsigned short type, std::string table_name, MYSQL_STMT* stmt)
: TableBase(MAX_FIELD, type, table_name, stmt)
{
	memset(m_param, 0, sizeof(m_param));
	PARAM_BIND(id,			MYSQL_TYPE_LONG);
	PARAM_BIND(account,		MYSQL_TYPE_LONG);
	PARAM_BIND(password,	MYSQL_TYPE_LONG);
	PARAM_BIND_STR(name, MYSQL_TYPE_VAR_STRING, 32);
	PARAM_BIND(last_time,	MYSQL_TYPE_TIMESTAMP);

	m_field_name[id]		= "id";
	m_field_name[account]	= "account";
	m_field_name[password]	= "password";
	m_field_name[name]		= "name";
	m_field_name[last_time] = "last_time";
}


// 字符串需要重新绑定缓冲区
// bool TB_Login::BindResult()
// {
// 	BIND_RESULT_BEGIN();
// 	FIELD(NAME).data = (char *)MemoryVL::Instance().Malloc(fields[NAME].length);
// 	m_param[NAME].buffer = FIELD(NAME).data;
// 	m_param[NAME].buffer_length = fields[NAME].length;
// 	BIND_RESULT_END();
// }
// 
// bool TB_Login::HasResult()
// {
// 	if (!TableBase::HasResult()/* || m_result == NULL*/)
// 	{
// 		return false;
// 	}
// 	return true;
// }
