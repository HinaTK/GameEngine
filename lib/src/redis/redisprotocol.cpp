
#include <stdio.h>
#include "redisprotocol.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/mem.h"


RedisData::RedisData(char _type, unsigned int _len, const char *buf)
: type(_type)
, len(_len)
{
	data = Mem::Alloc(len);
	memcpy(data, buf, len);
}

RedisData::~RedisData()
{
	Mem::Free(data);
}

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

REGISTER_MEMORYPOOL(gamememorypool, RedisData, 64);
REGISTER_MEMORYPOOL(gamememorypool, RedisBulkData, 64);

bool RedisBulkData::Push(char type, unsigned int len, const char *buf)
{
	RedisData *data = new RedisData(type, len, buf);
	data_list.push_back(data);
	return true;
}

#define CheckEndLine(buf, len)\
	unsigned int end_len = EndLine(buf, len);\
	if (end_len == RedisProtocol::OPR_MORE_DATA)\
	{\
		return RedisProtocol::OPR_MORE_DATA; \
	}

static unsigned int	EndLine(const char *buf, unsigned int len);
static int			ReadNumber(const char *buf, unsigned int len);
static char			_ReadString(const char *buf, unsigned int left_len, int &read_len, RedisData **data);
static int			ReadMessage(char type, const char *buf, unsigned int len, RedisBulkData **bulk_data);
static int			ReadInteger(const char *buf, unsigned int len, RedisBulkData **bulk_data);
static int			ReadString(const char *buf, unsigned int len, RedisBulkData **bulk_data);
static int			ReadArray(const char *buf, unsigned int left_len, RedisBulkData **bulk_data);

/*
	:1\r\n	前缀 + 结果 + 结束 最少也要有4个字节
*/
int RedisProtocol::Decode(const char *buf, unsigned int len, RedisBulkData **bulk_data)
{
	if (len < 4)
	{
		return OPR_MORE_DATA;
	}

	switch (buf[0])
	{
	case '+':
		return ReadMessage(REPLY_TYPE_OK, buf + 1, len - 1, bulk_data);
	case '-':
		return ReadMessage(REPLY_TYPE_ERROR, buf + 1, len - 1, bulk_data);
	case ':':
		return ReadInteger(buf + 1, len - 1, bulk_data);
	case '$':
		return ReadString(buf + 1, len - 1, bulk_data);
	case '*':
		return ReadArray(buf + 1, len - 1, bulk_data);
	default:
		return OPR_DATA_INVALID;
	}

	return OPR_DATA_INVALID;
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
		return RedisProtocol::OPR_MORE_DATA;
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
	CheckEndLine(buf, left_len);
	read_len = read_len + end_len + 2;
	int number = ReadNumber(buf, end_len);
	if (number <= 0)
	{
		*data = new RedisData(RedisProtocol::REPLY_TYPE_STRING_ERROR, sizeof(number), (const char *)&number);
	}
	else
	{
		end_len = EndLine(buf + read_len, left_len - read_len);
		if (end_len == RedisProtocol::OPR_MORE_DATA)
		{
			return RedisProtocol::OPR_MORE_DATA;
		}

		*data = new RedisData(RedisProtocol::REPLY_TYPE_STRING, end_len, buf + read_len);
		read_len = read_len + end_len + 2;
	}
	return RedisProtocol::OPR_SUCCESS;
}

int ReadMessage(char type, const char *buf, unsigned int len, RedisBulkData **bulk_data)
{
	CheckEndLine(buf, len);
	*bulk_data = new RedisBulkData();
	(*bulk_data)->Push(type, end_len, buf);
	// 前缀 + 结束符 = 3字节
	return end_len + 3;
}

int ReadInteger(const char *buf, unsigned int len, RedisBulkData **bulk_data)
{
	CheckEndLine(buf, len);
	int number = ReadNumber(buf, end_len);
	*bulk_data = new RedisBulkData();
	(*bulk_data)->Push(RedisProtocol::REPLY_TYPE_INTEGER, sizeof(number), (const char *)&number);
	// 前缀 + 结束符 = 3字节
	return end_len + 3;
}

int ReadString(const char *buf, unsigned int left_len, RedisBulkData **bulk_data)
{
	RedisData *data;
	int read_len = 0;
	int ret = _ReadString(buf, left_len, read_len, &data);
	if (ret != RedisProtocol::OPR_DATA_INVALID)
	{
		*bulk_data = new RedisBulkData();
		(*bulk_data)->Push(data);
		return read_len + 1;
	}
	return ret;
}

int ReadArray(const char *buf, unsigned int left_len, RedisBulkData **bulk_data)
{
	int read_len = 0;
	int sub_read_len = 0;
	CheckEndLine(buf, left_len);
	int number = ReadNumber(buf, end_len);

	read_len = end_len + 2;
	buf = buf + end_len + 2;
	if (number <= 0)
	{
		*bulk_data = new RedisBulkData();
		(*bulk_data)->Push(RedisProtocol::REPLY_TYPE_ARRAY_ERROR, sizeof(number), (const char *)&number);
	}
	else
	{
		*bulk_data = new RedisBulkData();
		for (int i = 0; i < number; ++i)
		{
			RedisData *data = NULL;
			sub_read_len = 0;
			int ret = _ReadString(buf + 1, left_len - read_len, sub_read_len, &data);
			if (ret == RedisProtocol::OPR_DATA_INVALID)
			{
				delete *bulk_data;
				*bulk_data = NULL;
				return ret;
			}

			(*bulk_data)->Push(data);
			// 这里 +1 是前缀的一个字节
			read_len = read_len + 1 +sub_read_len;
			buf = buf + 1 + sub_read_len;
		}	
	}
	
	return read_len + 1;
}
