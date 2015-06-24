
#include <stdio.h>
#include "redisprotocol.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/mem.h"

class RedisData
{
public:
	RedisData(const char *buf, unsigned int _len)
		: len(_len)
	{
		data = Mem::Alloc(len);
		memcpy(data, buf, len);
	}
	~RedisData(){ Mem::Free(data); }
	unsigned int	len;
	char *			data;

	void *	operator new(size_t c);
	void	operator delete(void *m);
};

REGISTER_MEMORYPOOL(gamememorypool, RedisData, 64);
REGISTER_MEMORYPOOL(gamememorypool, RedisBulkData, 64);

RedisBulkData::~RedisBulkData()
{
	std::list<RedisData *>::iterator itr = data_list.begin();
	for (; itr != data_list.begin(); ++itr)
	{
		if ((*itr) != NULL)
		{
			delete (*itr);
			(*itr) = NULL;
		}
	}
}

bool RedisBulkData::Push(const char *buf, unsigned int len)
{
	RedisData *data = new RedisData(buf, len);
	data_list.push_back(data);
	return true;
}

static unsigned int	EndLine(const char *buf, unsigned int len);
static int			ReadNumber(const char *buf, unsigned int len);
static char			_ReadString(const char *buf, unsigned int left_len, int &read_len, RedisData **data);
static int			ReadMessage(char type, const char *buf, unsigned int len, RedisBulkData **bulk_data);
static int			ReadInteger(const char *buf, unsigned int len, RedisBulkData **bulk_data);
static int			ReadString(const char *buf, unsigned int len, RedisBulkData **bulk_data);
static int			ReadArray(const char *buf, unsigned int left_len, RedisBulkData **bulk_data);

/*
	+OK\r\n	前缀 + 结果 + 结束 最少也要有4个字节
*/
int RedisProtocol::Decode(const char *buf, unsigned int len, RedisBulkData **bulk_data)
{
	if (len < 4)
	{
		return REPLY_TYPE_MORE_DATA;
	}

	unsigned int end_len = EndLine(buf + 1, len - 1);
	if (end_len == 0)
	{
		return REPLY_TYPE_DATA_INVALID;
	}

	switch (buf[0])
	{
	case '+':
		return ReadMessage(REPLY_TYPE_OK, buf + 1, end_len, bulk_data) + 1;
	case '-':
		return ReadMessage(REPLY_TYPE_ERROR, buf + 1, end_len, bulk_data) + 1;
	case ':':
		return ReadInteger(buf + 1, end_len, bulk_data) + 1;
	case '$':
		return ReadString(buf + 1, len - 1, bulk_data) + 1;
	case '*':
		return ReadArray(buf + 1, len - 1, bulk_data) + 1;
	default:
		return REPLY_TYPE_DATA_INVALID;
	}

	return REPLY_TYPE_DATA_INVALID;
}

unsigned int EndLine(const char *buf, unsigned int len)
{
	unsigned int i = 0;
	while (i < (len - 1))
	{
		if (buf[i] == '\r' && buf[i + 1] == '\n')
		{
			return i;
		}
		++i;
	}

	if (i >= (len - 1))
	{
		return RedisProtocol::REPLY_TYPE_MORE_DATA;
	}
	return i;
}

int ReadNumber(const char *buf, unsigned int len)
{
	int ret = 0;
	int temp = 0;
	unsigned int i = 0;
	if (buf[0] == '-')
	{
		i = 1;
	}

	for (; i < len; ++i)
	{
		temp = buf[i] - '0';

		if (temp >= 10 || temp < 0)
		{
			return -1;
		}

		ret *= 10;
		ret += temp;
	}

	if (buf[0] == '-')
	{
		return -ret;
	}
	
	return ret;
}

char _ReadString(const char *buf, unsigned int left_len, int &read_len, RedisData **data)
{
	unsigned int end_len = EndLine(buf, left_len);
	if (end_len == 0)
	{
		return RedisProtocol::REPLY_TYPE_DATA_INVALID;
	}
	read_len = read_len + end_len + 2;
	int number = ReadNumber(buf, end_len);
	if (number <= 0)
	{
		*data = new RedisData((const char *)&number, sizeof(number));
		return RedisProtocol::REPLY_TYPE_STRING_ERROR;
	}
	else
	{
		end_len = EndLine(buf + read_len, left_len - read_len);
		if (end_len == 0)
		{
			return RedisProtocol::REPLY_TYPE_DATA_INVALID;
		}

		*data = new RedisData(buf + read_len, end_len);
		read_len = read_len + end_len + 2;
		return RedisProtocol::REPLY_TYPE_STRING;
	}
	return RedisProtocol::REPLY_TYPE_DATA_INVALID;
}

int ReadMessage(char type, const char *buf, unsigned int len, RedisBulkData **bulk_data)
{
	*bulk_data = new RedisBulkData();
	(*bulk_data)->type = type;
	(*bulk_data)->Push(buf + 1, len);
	return len + 2;
}

int ReadInteger(const char *buf, unsigned int len, RedisBulkData **bulk_data)
{
	int number = ReadNumber(buf, len);
	*bulk_data = new RedisBulkData();
	(*bulk_data)->type = RedisProtocol::REPLY_TYPE_INTEGER;
	(*bulk_data)->Push((const char *)&number, sizeof(number));
	return len + 2;
}

int ReadString(const char *buf, unsigned int len, RedisBulkData **bulk_data)
{
	RedisData *data;
	int read_len = 0;
	int ret = _ReadString(buf + 1, len - 1, read_len, &data);
	if (ret != RedisProtocol::REPLY_TYPE_DATA_INVALID)
	{
		*bulk_data = new RedisBulkData();
		(*bulk_data)->type = ret;
		(*bulk_data)->Push(data);
		return read_len;
	}
	return 0;
}

int ReadArray(const char *buf, unsigned int left_len, RedisBulkData **bulk_data)
{
	int read_len = 0;
	int sub_read_len = 0;
	unsigned int end_len = EndLine(buf, left_len);
	if (end_len == 0)
	{
		return RedisProtocol::REPLY_TYPE_DATA_INVALID;
	}
	int number = ReadNumber(buf, end_len);

	read_len = end_len + 2;
	buf = buf + end_len + 2;
	if (number <= 0)
	{
		*bulk_data = new RedisBulkData();
		(*bulk_data)->type = RedisProtocol::REPLY_TYPE_ARRAY_ERROR;
		(*bulk_data)->Push((const char *)&number, sizeof(number));
	}
	else
	{
		*bulk_data = new RedisBulkData();
		(*bulk_data)->type = RedisProtocol::REPLY_TYPE_ARRAY;
		for (int i = 0; i < number; ++i)
		{
			RedisData *data = NULL;
			sub_read_len = 0;
			int ret = _ReadString(buf + 1, left_len - read_len, sub_read_len, &data);
			if (ret == RedisProtocol::REPLY_TYPE_DATA_INVALID)
			{
				delete *bulk_data;
				*bulk_data = NULL;
				return RedisProtocol::REPLY_TYPE_DATA_INVALID;
			}

			(*bulk_data)->Push(data);
			// 这里 +1 是前缀的一个字节
			read_len = read_len + 1 +sub_read_len;
			buf = buf + 1 + sub_read_len;
		}	
	}
	
	return read_len;
}
