
#include <stdio.h>
#include "redisprotocol.h"
#include "lib/include/common/memoryvl.h"

RedisProtocol::RedisProtocol()
: m_data_num(0)
, m_redis_data(NULL)
{

}

RedisProtocol::~RedisProtocol()
{
// 	if (m_redis_data)
// 	{
// 	}
}

/*
	+OK\r\n	前缀 + 结果 + 结束 最少也要有4个字节
*/
bool RedisProtocol::Decode(char *buf, unsigned int len)
{
	if (len < 4)
	{
		return false;
	}
	int data_len = 0;
	switch (buf[0])
	{
	case '+':		
		data_len = FindNextLine(buf + 1, len - 1);
		if (data_len == 0)
		{
			return false;
		}

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
		return false;
	}
}

int RedisProtocol::FindNextLine(char *buf, unsigned int len)
{
	int i = 0;
	while (i < (len - 1))
	{
		if (buf[i] == '\r' && buf[i + 1] == '\n')
		{
			return i;
		}
		++i;
	}
	return 0;
}
