
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
	+OK\r\n	ǰ׺ + ��� + ���� ����ҲҪ��4���ֽ�
*/
bool RedisProtocol::Decode(char *buf, unsigned int len)
{
	if (len < 4)
	{
		return false;
	}
	switch (buf[0])
	{
	case '+':
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
