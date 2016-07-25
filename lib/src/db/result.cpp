
#include "result.h"
#include "prepare.h"
#include "handler.h"

MysqlResult::MysqlResult(MysqlPrepare *prepare)
{
	MysqlHandler *handle = prepare->GetHandle();
	m_metadata = mysql_stmt_result_metadata(prepare->GetStmt());
	if (0 == m_metadata)
	{
		return;
	}

	field_num = mysql_num_fields(m_metadata);
	if (field_num < 1)
	{
		return;
	}

	result = new MYSQL_BIND[field_num];
	memset(result, 0, sizeof(MYSQL_BIND) * field_num);
	MYSQL_FIELD* fields = mysql_fetch_fields(m_metadata);
	for (unsigned int i = 0; i < field_num; ++i)
	{
		result[i].is_null = (my_bool *)handle->Get1Pool()->Alloc();
		switch (fields[i].type)
		{
		case MYSQL_TYPE_TINY:
			result[i].buffer = handle->Get1Pool()->Alloc();
		case MYSQL_TYPE_SHORT:
			result[i].buffer = handle->Get2Pool()->Alloc();
		case MYSQL_TYPE_LONG:
		case MYSQL_TYPE_FLOAT:
			result[i].buffer = handle->Get4Pool()->Alloc();
			break;
		case MYSQL_TYPE_LONGLONG:
		case MYSQL_TYPE_DOUBLE:
			result[i].buffer = handle->Get8Pool()->Alloc();
			break;
		case MYSQL_TYPE_VARCHAR:
		case MYSQL_TYPE_VAR_STRING:
		case MYSQL_TYPE_STRING:
		case MYSQL_TYPE_TINY_BLOB:
		case MYSQL_TYPE_MEDIUM_BLOB:
		case MYSQL_TYPE_LONG_BLOB:
		case MYSQL_TYPE_BLOB:
			// todo 确认length这样做是不是对的
			result[i].buffer = new char[fields[i].length];
			result[i].length = &fields[i].length;
			break;
		default:
			break;
		}
	}
	// todo 判断错误
	mysql_stmt_bind_result(prepare->GetStmt(), result);
}

#define CHECK_INDEX(index) \
	if (index >= field_num)\
	{\
		return false;\
	}

bool MysqlResult::Read(unsigned int index, char &val)
{
	CHECK_INDEX(index);
	val = *(char *)result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, short &val)
{
	CHECK_INDEX(index);
	val = *(short *)result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, int &val)
{
	CHECK_INDEX(index);
	val = *(int *)result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, long long &val)
{
	CHECK_INDEX(index);
	val = *(long long *)result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, float &val)
{
	CHECK_INDEX(index);
	val = *(float *)result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, double &val)
{
	CHECK_INDEX(index);
	val = *(double *)result[index].buffer;
	return true;
}

bool MysqlResult::Read(unsigned int index, char *val)
{
	CHECK_INDEX(index);
	memcpy(val, result[index].buffer, *result[index].length);
	return true;
}

bool MysqlResult::Read(unsigned int index, char *val, unsigned int len)
{
	CHECK_INDEX(index);
	size_t real_len = len > *result[index].length ? *result[index].length : len - 1;
	memcpy(val, result[index].buffer, real_len);
	val[real_len] = 0;
	return true;
}

int MysqlResult::FieldLength(unsigned int index)
{
	if (index >= field_num)
	{
		return -1;
	}
	return (int)result[index].length;
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

