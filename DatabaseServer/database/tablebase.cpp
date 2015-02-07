
#include "tablebase.h"
#include "libcommon/memoryvl.h"

static const char *relationType[] = { ">", "=", "<", ">=", "<=", "<>" };
static const char *connectType[] = { " AND ", " OR " };

#define SETSYMBOL(str)\
	static std::string symbol = ""; \
	symbol = ""; \
if (!is_end) symbol = str; 

#define CHECKRELATION(r)\
if (r >= TableBase::MAX_RELATION)\
{\
	return; \
}

#define CHECKCONNECT(c)\
if (c >= TableBase::MAX_CONNECT)\
{\
	return; \
}

#define CHECKOPERATION(o)\
if (o >= TableBase::MAX_OPERATION)\
{\
	return; \
}


TableBase::TableBase(unsigned short table_type, std::string table_name, MYSQL_STMT* stmt)
: m_table_type(table_type)
, m_table_name(table_name)
, m_stmt(stmt)
, m_result(NULL)
{
	
}

void TableBase::Init()
{
	int max_field = MaxField();
	std::string *fields = FieldsName();

	m_insert_base = "INSERT INTO " + m_table_name + " (";
	std::string val;
	for (int i = 0; i < max_field; ++i)
	{
		m_insert_base += fields[i] + ",";
		val += "?,";
	}
	m_insert_base.replace(m_insert_base.size() - 1, 1, ") VALUES (");
	val.replace(val.size() - 1, 1, ");");
	m_insert_base += val;

	m_select_base = "SELECT ";
	for (int i = 0; i < max_field; ++i)
	{
		m_select_base += fields[i] + ",";
	}
	m_select_base.replace(m_select_base.size() - 1, 1, " FROM ");
	m_select_base += m_table_name + " ";

	m_update_base = "UPDATE " + m_table_name + "SET";
	for (int i = 0; i <max_field; ++i)
	{
		m_update_base += fields[i] + "=(?),";
	}
	m_update_base.replace(m_update_base.size() - 1, 1, "");

	m_delete_base = "DELETE FROM " + m_table_name;
}

bool TableBase::Insert()
{
	BindParam();
	if (0 != mysql_stmt_prepare(m_stmt, m_insert_base.c_str(), m_insert_base.size()) ||
		0 != mysql_stmt_bind_param(m_stmt, GetParam()) ||
		0 != mysql_stmt_execute(m_stmt))
	{
		return false;
	}
	return true;
}

bool TableBase::Select()
{
	std::string select_sql = m_select_base;
	if (m_condition[SELECT_OPER] != "")
	{
		select_sql = select_sql + " WHERE " + m_condition[SELECT_OPER];
		m_condition[SELECT_OPER] = "";
	}

	select_sql += ";";
	if (0 != mysql_stmt_prepare(m_stmt, select_sql.c_str(), select_sql.length() + 1) ||
		//0 != mysql_stmt_bind_param(m_stmt, GetParam()) ||
		0 != mysql_stmt_execute(m_stmt))
	{
		return false;
	}
	
	return true;
}

bool TableBase::Update()
{
	if (m_condition[UPDATE_OPER] == "")
	{
		return false;
	}
	std::string update_sql = m_update_base;
	update_sql += " WHERE " + m_condition[UPDATE_OPER] + ";";
	if (0 != mysql_stmt_prepare(m_stmt, update_sql.c_str(), update_sql.size()) ||
		0 != mysql_stmt_bind_param(m_stmt, GetParam()) ||
		0 != mysql_stmt_execute(m_stmt))
	{
		return false;
	}
	return true;
}

bool TableBase::Delete()
{
	std::string delete_sql = m_delete_base;
	if (m_condition[DELETE_OPER] != "")
	{
		delete_sql += " WHERE " + m_condition[DELETE_OPER];
	}
	delete_sql += ";";
	if (0 != mysql_stmt_prepare(m_stmt, delete_sql.c_str(), delete_sql.size()) ||
		0 != mysql_stmt_bind_param(m_stmt, GetParam()) ||
		0 != mysql_stmt_execute(m_stmt))
	{
		return false;
	}
	return true;
}

void TableBase::SetCondition(std::string field, int val, unsigned int relation, unsigned int oper, bool is_end /*= false*/, unsigned int connect /*= AND*/)
{
	CHECKRELATION(relation);
	CHECKCONNECT(connect);
	CHECKOPERATION(oper);
	SETSYMBOL(connectType[connect]);
	static char strVal[32];
	sprintf(strVal, "%d", val);

	m_condition[oper] = m_condition[oper] + field + relationType[relation] + strVal + symbol;
}

void TableBase::SetCondition(std::string field, std::string val, unsigned int relation, unsigned int oper, bool is_end /*= false*/, unsigned int connect /*= AND*/)
{
	CHECKRELATION(relation);
	CHECKCONNECT(connect);
	CHECKOPERATION(oper);
	SETSYMBOL(connectType[connect]);

	m_condition[oper] = m_condition[oper] + field + relationType[relation] + val + symbol;
}

bool TableBase::HasResult()
{
	if (mysql_stmt_fetch(m_stmt) == 0)
	{
		return true;
	}
	return false;
}

// bool TableBase::BindResult(std::vector<unsigned int> &results)
// {
// 	if (results.size() <= 0)
// 	{
// 		return true;
// 	}
// 	MYSQL_RES *m_metadata = mysql_stmt_result_metadata(m_stmt);
// 	if (NULL == m_metadata)
// 	{
// 		return false;
// 	}
// 	unsigned int field_num = mysql_num_fields(m_metadata);
// 	MYSQL_FIELD* fields = mysql_fetch_fields(m_metadata);
// 	if (fields == NULL)
// 	{
// 		return false;
// 	}
// 	MYSQL_BIND *bind_result = GetParam();
// 	for (std::vector<unsigned int>::iterator itr = results.begin(); itr != results.end(); ++itr)
// 	{
// 		if ((*itr) >= field_num)
// 		{
// 			continue;
// 		}
// 		bind_result[(*itr)].buffer = (char *)MemoryVL::Instance().Malloc(fields[(*itr)].length);
// 		bind_result[(*itr)].buffer_length = fields[(*itr)].length;
// 	}
// 	if (0 != mysql_stmt_bind_result(m_stmt, bind_result))
// 	{
// 		return false;
// 	}
// 	return true;
// }

