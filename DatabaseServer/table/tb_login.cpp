
#include "tb_login.h"

TB_Login::TB_Login( std::string table_name )
: GameMysqlStmt(table_name)
{
	m_cache.FieldDefine(ID,			DT_INT, 4);
	m_cache.FieldDefine(ACCOUNT,	DT_INT, 4);
	m_cache.FieldDefine(PASSWORD,	DT_INT, 4);
	m_cache.FieldDefine(NAME,		DT_STR, 32);
	m_cache.FieldDefine(LAST_TIME,	DT_INT, 4);
}

std::string * TB_Login::GetFields()
{
	return m_field_name;
}
