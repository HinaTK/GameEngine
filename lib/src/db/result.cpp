
#include "result.h"
#include "prepare.h"

MysqlResult::MysqlResult(MysqlPrepare *prepare)
{
	m_metadata = mysql_stmt_result_metadata(prepare->GetStmt());
	if (0 == m_metadata)
	{
		return;
	}

	unsigned int field_num = mysql_num_fields(m_metadata);
	if (field_num < 1)
	{
		return;
	}

	result = new MYSQL_BIND[field_num];
	MYSQL_FIELD* fields = mysql_fetch_fields(m_metadata);
	for (unsigned int i = 0; i < field_num; ++i)
	{
		switch (fields[i].type)
		{
		case MYSQL_TYPE_LONG:
			result[i].buffer = prepare->Get4Pool()->Alloc();
		case MYSQL_TYPE_TINY_BLOB:
		case MYSQL_TYPE_MEDIUM_BLOB:
		case MYSQL_TYPE_LONG_BLOB:
		case MYSQL_TYPE_BLOB:
			result[i].buffer = new char[fields[i].length];
			result[i].is_null = (my_bool *)prepare->Get1Pool()->Alloc();
			break;
		default:
			break;
		}
	}
	// todo ÅÐ¶Ï´íÎó
	mysql_stmt_bind_result(prepare->GetStmt(), result);
}

MysqlResult::~MysqlResult()
{
	if (result != NULL)
	{
		delete[] result;
		result = NULL;
	}

	if (m_metadata != NULL)
	{
		mysql_free_result(m_metadata);
		m_metadata = NULL;
	}
}

