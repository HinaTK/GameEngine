
#include <stdio.h>
#include "redisprotocol.h"
#include "lib/include/common/memoryvl.h"


bool RedisBlukData::Push(char *buf, unsigned int len)
{
	RedisData *data = new RedisData(buf, len);
	m_data_list.push_back(data);
	return true;
}


/*
	+OK\r\n	前缀 + 结果 + 结束 最少也要有4个字节
*/
unsigned int RedisProtocol::Decode(char *buf, unsigned int len, RedisBlukData **bulk_data)
{
	if (len < 4)
	{
		return false;
	}
	unsigned int read_len = 0;
	switch (buf[0])
	{
	case '+':
		read_len = EndLine(buf + 1, len - 1);
		if (read_len == 0)
		{
			return 0;
		}
		*bulk_data = new RedisBlukData();
		(*bulk_data)->SetType(RT_OK);
		(*bulk_data)->Push(buf + 1, read_len);
		break;
	case '-':
		break;
	case ':':
		break;
	case '$':
		break;
	case '*':
		break;
	default:
		return 0;
	}

	return read_len;
}

unsigned int RedisProtocol::EndLine(char *buf, unsigned int len)
{
	unsigned int i = 0;
	while (i < (len - 1))
	{
		if (buf[i] == '\r' && buf[i + 1] == '\n')
		{
			return i;
		}
	}

	if (i >= (len - 1))
	{
		return 0;
	}
	return i;
}
