
#ifndef REDIS_PROTOCOL_H
#define REDIS_PROTOCOL_H

#include <list>

class RedisData
{
public:
	RedisData(char _type, unsigned int _len, const char *buf);	
	~RedisData();

	char			type;
	unsigned int	len;
	char *			data;

	void *	operator new(size_t c);
	void	operator delete(void *m);
};

class RedisBulkData
{
public:
	RedisBulkData(){}
	~RedisBulkData();

	bool	Push(char type, unsigned int len, const char *buf);
	void	Push(RedisData *data){ data_list.push_back(data); }

	void *	operator new(size_t c);
	void	operator delete(void *m);

	std::list<RedisData *>	data_list;
};

namespace RedisProtocol
{
	// ²Ù×÷½á¹û
	enum
	{
		OPR_DATA_INVALID = -1,
		OPR_MORE_DATA,
		OPR_SUCCESS
	};

	enum ReplyType
	{
		REPLY_TYPE_OK,
		REPLY_TYPE_ERROR,
		REPLY_TYPE_INTEGER,
		REPLY_TYPE_STRING_ERROR,
		REPLY_TYPE_STRING,
		REPLY_TYPE_ARRAY_ERROR,
	};

	int	Decode(const char *buf, unsigned int len, RedisBulkData **bulk_data);
};

#endif