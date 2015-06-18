
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

class RedisBulkData
{
public:
	RedisBulkData(): m_type(-1){}
	~RedisBulkData()
	{
		std::list<RedisData *>::iterator itr = m_data_list.begin();
		for (; itr != m_data_list.begin(); ++itr)
		{
			if ((*itr) != NULL)
			{
				delete (*itr);
				(*itr) = NULL;
			}
		}
	};

	void	SetType(char type){ m_type = type; }
	bool	Push(const char *buf, unsigned int len);
	void	Push(RedisData *data){ m_data_list.push_back(data); }
private:
	char	m_type;
	std::list<RedisData *>	m_data_list;
};

namespace RedisProtocol
{
	enum ReplyType
	{
		REPLY_TYPE_DATA_INVALID = -1,
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