
#include "result.h"
#include "prepare.h"
#include "handler.h"
#include "lib/include/base/function.h"

MysqlResult::MysqlResult(MysqlPrepare *prepare)
: m_result(NULL)
, m_metadata(NULL)
, m_handler(prepare->GetHandler())
{
	m_metadata = mysql_stmt_result_metadata(prepare->GetStmt());
	if (0 == m_metadata)
	{
		return;
	}

	m_field_num = mysql_num_fields(m_metadata);
	if (m_field_num < 1)
	{
		return;
	}

	m_result = new MYSQL_BIND[m_field_num];
	memset(m_result, 0, sizeof(MYSQL_BIND) * m_field_num);
	MYSQL_FIELD* fields = mysql_fetch_fields(m_metadata);
	for (unsigned int i = 0; i < m_field_num; ++i)
	{
		m_result[i].buffer_type = fields[i].type;
		//m_result[i].is_null = (my_bool *)m_handler->Get1Pool()->Alloc();
		switch (fields[i].type)
		{
		case MYSQL_TYPE_TINY:
			m_result[i].buffer = m_handler->Get1Pool()->Alloc();
			break;
		case MYSQL_TYPE_SHORT:
			m_result[i].buffer = m_handler->Get2Pool()->Alloc();
			break;
		case MYSQL_TYPE_LONG:
		case MYSQL_TYPE_FLOAT:
			m_result[i].buffer = m_handler->Get4Pool()->Alloc();
			break;
		case MYSQL_TYPE_LONGLONG:
		case MYSQL_TYPE_DOUBLE:
			m_result[i].buffer = m_handler->Get8Pool()->Alloc();
			break;
		case MYSQL_TYPE_VARCHAR:
		case MYSQL_TYPE_VAR_STRING:
		case MYSQL_TYPE_STRING:
		case MYSQL_TYPE_TINY_BLOB:
		case MYSQL_TYPE_MEDIUM_BLOB:
		case MYSQL_TYPE_LONG_BLOB:
		case MYSQL_TYPE_BLOB:
			// todo make a pool,because alway return max len
			m_result[i].buffer = new char[fields[i].length + 1];
			m_result[i].length = &fields[i].length;
			m_result[i].buffer_length = fields[i].length;
			break;
		default:
			break;
		}
	}
	
	if (mysql_stmt_bind_result(prepare->GetStmt(), m_result) != 0)
	{
		Function::Error("mysql_stmt_bind_result error");
	}
}

MysqlResult::~MysqlResult()
{
	if (m_result != NULL)
	{
		for (unsigned int i = 0; i < m_field_num; ++i)
		{
			switch (m_result[i].buffer_type)
			{
			case MYSQL_TYPE_TINY:
				m_handler->Get1Pool()->Free(m_result[i].buffer);
				break;
			case MYSQL_TYPE_SHORT:
				m_handler->Get2Pool()->Free(m_result[i].buffer);
				break;
			case MYSQL_TYPE_LONG:
			case MYSQL_TYPE_FLOAT:
				m_handler->Get4Pool()->Free(m_result[i].buffer);
				break;
			case MYSQL_TYPE_LONGLONG:
			case MYSQL_TYPE_DOUBLE:
				m_handler->Get8Pool()->Free(m_result[i].buffer);
				break;
			case MYSQL_TYPE_VARCHAR:
			case MYSQL_TYPE_VAR_STRING:
			case MYSQL_TYPE_STRING:
			case MYSQL_TYPE_TINY_BLOB:
			case MYSQL_TYPE_MEDIUM_BLOB:
			case MYSQL_TYPE_LONG_BLOB:
			case MYSQL_TYPE_BLOB:
				// todo make a pool,because alway return max len
				delete m_result[i].buffer;
				break;
			default:
				break;
			}
		}
		delete[] m_result;
		m_result = NULL;
	}

	if (m_metadata != NULL)
	{
		mysql_free_result(m_metadata);
		m_metadata = NULL;
	}
}

#define CHECK_INDEX(index) \
	if (index >= m_field_num)\
	{\
		return false;\
	}

bool MysqlResult::Read(unsigned int index, char &val)
{
	CHECK_INDEX(index);
	val = *(char *)m_result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, short &val)
{
	CHECK_INDEX(index);
	val = *(short *)m_result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, int &val)
{
	CHECK_INDEX(index);
	val = *(int *)m_result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, unsigned int &val)
{
	CHECK_INDEX(index);
	val = *(unsigned int *)m_result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, long long &val)
{
	CHECK_INDEX(index);
	val = *(long long *)m_result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, float &val)
{
	CHECK_INDEX(index);
	val = *(float *)m_result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, double &val)
{
	CHECK_INDEX(index);
	val = *(double *)m_result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, char *val)
{
	CHECK_INDEX(index);
	memcpy(val, m_result[index].buffer, *m_result[index].length);
	return true;
}

bool MysqlResult::Read(unsigned int index, char *val, unsigned int len)
{
	CHECK_INDEX(index);
	size_t real_len = len > *m_result[index].length ? *m_result[index].length : len - 1;
	memcpy(val, m_result[index].buffer, real_len);
	val[real_len] = 0;
	return true;
}

char* MysqlResult::ReadStr(unsigned int index, int &val)
{
	if (index > m_field_num) return NULL;
	
	val = *m_result[index].length;
	char *ret = (char *)m_result[index].buffer;
	ret[val] = 0;
	return ret;
}

int MysqlResult::FieldLength(unsigned int index)
{
	if (index >= m_field_num) return -1;
	return (int)m_result[index].length;
}


