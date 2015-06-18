
#ifndef REDIS_PROTOCOL_H
#define REDIS_PROTOCOL_H

#include <list>

class RedisData
{
public:
	RedisData(const char *buf, unsigned int _len)
		: len(_len)
	{
		data = new char(len);
		memcpy(data, buf, len);
	}
	~RedisData(){ delete data; }
	unsigned int	len;
	char *			data;
};

class RedisBlukData
{
public:
	RedisBlukData()
		: m_type(-1)
	{}
	~RedisBlukData();

	void	SetType(char type){ m_type = type; }
	bool	Push(const char *buf, unsigned int len);

private:
	char	m_type;
	std::list<RedisData *>	m_data_list;
};

namespace RedisProtocol
{
	enum ReplyType
	{
		REPLY_TYPE_OK,
		REPLY_TYPE_ERROR,
		REPLY_TYPE_INTEGER,
		REPLY_TYPE_STRING,
		REPLY_TYPE_ARRAY
	};

	unsigned int	Decode(const char *buf, unsigned int len, RedisBlukData **bulk_data);

	unsigned int	EndLine(const char *buf, unsigned int len);
};

#endif