
#include <stdio.h>
#include "redisprotocol.h"
#include "lib/include/common/memoryvl.h"


bool RedisBulkData::Push(const char *buf, unsigned int len)
{
	RedisData *data = new RedisData(buf, len);
	m_data_list.push_back(data);
	return true;
}

static unsigned int	EndLine(const char *buf, unsigned int len);
static int			ReadNumber(const char *buf, unsigned int len);
static char			ReadString(const char *buf, unsigned int left_len, unsigned int &read_len, RedisData **data);
static char			ReadArray(const char *buf, unsigned int left_len, RedisBulkData **bulk_data);
/*
	+OK\r\n	前缀 + 结果 + 结束 最少也要有4个字节
*/
int RedisProtocol::Decode(const char *buf, unsigned int len, RedisBulkData **bulk_data)
{
	if (len < 4)
	{
		return 0;
	}


	unsigned int end_len = EndLine(buf + 1, len - 1);
	if (end_len == 0)
	{
		return 0;
	}

	unsigned int read_len = 1 + end_len + 2;
	switch (buf[0])
	{
	case '+':
		*bulk_data = new RedisBulkData();
		(*bulk_data)->SetType(REPLY_TYPE_OK);
		(*bulk_data)->Push(buf + 1, end_len);
		break;
	case '-':
		break;
	case ':':
		break;
	case '$':
		{
			RedisData *data;
			int ret = ReadString(buf + 1, len - 1, read_len, &data);
			if (ret != REPLY_TYPE_DATA_INVALID)
			{
				*bulk_data = new RedisBulkData();
				(*bulk_data)->SetType(ret);
				(*bulk_data)->Push(data);
			}
			else
			{
				return 0;
			}
		}
		break;
	case '*':
		return ReadArray(buf + 1, len - 1, bulk_data) + 1;
		break;
	default:
		return 0;
	}

	return read_len;
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
		return 0;
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

char ReadString(const char *buf, unsigned int left_len, unsigned int &read_len, RedisData **data)
{
	unsigned int end_len = EndLine(buf, left_len);
	if (end_len == 0)
	{
		return RedisProtocol::REPLY_TYPE_DATA_INVALID;
	}
	read_len = read_len + end_len + 2;
	int number_len = ReadNumber(buf, end_len);
	if (number_len <= 0)
	{
		*data = new RedisData((const char *)&number_len, sizeof(number_len));
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

char ReadArray(const char *buf, unsigned int left_len, RedisBulkData **bulk_data)
{
	unsigned int read_len = 0;
	unsigned int sub_read_len = 0;
	unsigned int end_len = EndLine(buf, left_len);
	if (end_len == 0)
	{
		return -1;
	}
	int number = ReadNumber(buf, end_len);

	read_len = end_len + 2;
	buf = buf + end_len + 2;
	if (number <= 0)
	{
		*bulk_data = new RedisBulkData();
		(*bulk_data)->SetType(RedisProtocol::REPLY_TYPE_ARRAY_ERROR);
		(*bulk_data)->Push((const char *)&number, sizeof(number));
	}
	else
	{
		*bulk_data = new RedisBulkData();
		(*bulk_data)->SetType(RedisProtocol::REPLY_TYPE_ARRAY);
		for (int i = 0; i < number; ++i)
		{
			RedisData *data = NULL;
			sub_read_len = 0;
			int ret = ReadString(buf + 1, left_len - read_len, sub_read_len, &data);
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
