
#include "tb_login.h"

TB_Login::TB_Login( std::string table_name )
: GameMysqlStmt(table_name)
{
// 	m_cache.FieldDefine(ID,			DT_INT, 4);
// 	m_cache.FieldDefine(ACCOUNT,	DT_INT, 4);
// 	m_cache.FieldDefine(PASSWORD,	DT_INT, 4);
// 	m_cache.FieldDefine(NAME,		DT_STR, 32);
// 	m_cache.FieldDefine(LAST_TIME,	DT_INT, 4);

	PARAM_BIND(ID,			MYSQL_TYPE_LONG);
	PARAM_BIND(ACCOUNT,		MYSQL_TYPE_LONG);
	PARAM_BIND(PASSWORD,	MYSQL_TYPE_LONG);
	PARAM_BIND(NAME,		MYSQL_TYPE_VAR_STRING);
	PARAM_BIND(LAST_TIME,	MYSQL_TYPE_TIMESTAMP);
// 	GetParam[ID].buffer_type = MYSQL_TYPE_LONG;
// 	m_param[ID].buffer = &FIELD(ID);
// 	m_param[ID].length = 0;
}

std::string * TB_Login::GetFields()
{
	return m_field_name;
}
