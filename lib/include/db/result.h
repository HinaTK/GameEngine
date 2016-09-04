
#ifndef MYSQL_RESULT_H
#define MYSQL_RESULT_H

#include "lib/include/mysql/mysql.h"

class MysqlPrepare;
class MysqlHandler;
class MysqlResult
{
public:
	MysqlResult(MysqlPrepare *prepare);
	~MysqlResult();

	bool	Read(unsigned int index, char &val);
	bool	Read(unsigned int index, short &val);
	bool	Read(unsigned int index, int &val);
	bool	Read(unsigned int index, unsigned int &val);
	bool	Read(unsigned int index, long long &val);
	bool	Read(unsigned int index, float &val);
	bool	Read(unsigned int index, double &val);
	bool	Read(unsigned int index, char *val);
	bool	Read(unsigned int index, char *val, unsigned int len);

	char *	ReadStr(unsigned int index, int &len);

	inline int FieldLength(unsigned int index);

private:
	MYSQL_BIND 		*m_result;
	MYSQL_RES 		*m_metadata;
	MysqlHandler	*m_handler;
	unsigned int 	m_field_num;
};

#define READ_RESULT_BEGIN(Result)\
	MysqlResult *mr = new MysqlResult(&Result); \
	while (Result.HasResult())\
	{


#define READ_RESULT_END() \
	}\
	delete mr;

#endif