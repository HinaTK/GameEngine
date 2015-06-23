
#ifndef REDIS_PROTOCOL_H
#define REDIS_PROTOCOL_H

#include <list>

class RedisData;
class RedisBulkData
{
public:
	RedisBulkData(): type(-1){}
	~RedisBulkData();

	bool	Push(const char *buf, unsigned int len);
	void	Push(RedisData *data){ data_list.push_back(data); }

	void *	operator new(size_t c);
	void	operator delete(void *m);

	char	type;
	std::list<RedisData *>	data_list;
};

namespace RedisProtocol
{
	enum ReplyType
	{
		REPLY_TYPE_DATA_INVALID = -1,
		REPLY_TYPE_MORE_DATA,
		REPLY_TYPE_OK,
		REPLY_TYPE_ERROR,
		REPLY_TYPE_INTEGER,
		REPLY_TYPE_STRING_ERROR,
		REPLY_TYPE_STRING,
		REPLY_TYPE_ARRAY_ERROR,
		REPLY_TYPE_ARRAY,
	};

	int	Decode(const char *buf, unsigned int len, RedisBulkData **bulk_data);
};

#endif