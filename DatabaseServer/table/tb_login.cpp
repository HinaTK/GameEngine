
#include <string.h>
#include "tb_login.h"
#include "libcommon/memoryvl.h"

TB_Login::TB_Login(unsigned short type, std::string table_name, MYSQL_STMT* stmt)
: TableBase(MAX_FIELD, type, table_name, stmt)
{
	memset(m_param, 0, sizeof(m_param));
	PARAM_BIND(ID,			MYSQL_TYPE_LONG);
	PARAM_BIND(ACCOUNT,		MYSQL_TYPE_LONG);
	PARAM_BIND(PASSWORD,	MYSQL_TYPE_LONG);
	PARAM_BIND_STR(NAME, MYSQL_TYPE_VAR_STRING, 32);
	PARAM_BIND(LAST_TIME,	MYSQL_TYPE_TIMESTAMP);

	m_field_name[ID]		= "id";
	m_field_name[ACCOUNT]	= "account";
	m_field_name[PASSWORD]	= "password";
	m_field_name[NAME]		= "name";
	m_field_name[LAST_TIME] = "last_time";
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
