
#ifndef TEST_REDIS_H
#define TEST_REDIS_H

#include <string>
//#include "lib/include/redis/redisprotocol.h"

namespace TestRedis
{
//	void ShowBulkData(RedisBulkData *data)
//	{
		
//		std::list<RedisData *>::iterator itr = data->data_list.begin();
//		for (; itr != data->data_list.end(); ++itr)
//		{
//			printf("type = %d\n", (*itr)->type);
//			switch ((*itr)->type)
//			{
//			case RedisProtocol::REPLY_TYPE_INTEGER:
//			case RedisProtocol::REPLY_TYPE_STRING_ERROR:
//			case RedisProtocol::REPLY_TYPE_ARRAY_ERROR:
//				printf("data = %d\n", *(int *)(*itr)->data);
//				break;
//			default:
//				printf("data = %.*s\n", (*itr)->len, (*itr)->data);
//				break;
//			}
//		}
//	}

//	void Decode(char *reply)
//	{
////		RedisBulkData *data = NULL;
////		if (RedisProtocol::Decode(reply, strlen(reply), &data) <= RedisProtocol::OPR_MORE_DATA)
////		{
////			return;
////		}

////		ShowBulkData(data);
////		delete data;
//	}

//	// 短字符串
//	void Test1()
//	{
//		char *reply = "+OK\r\n";
//		Decode(reply);
//	}

//	// 错误
//	void Test2()
//	{
//		char *reply = "-ERR unknown command 'seet'\r\n";
//		Decode(reply);
//	}

//	// 整数
//	void Test3()
//	{
//		char *reply = ":11\r\n";
//		Decode(reply);
//	}

//	// 长字符串
//	void Test4()
//	{
//		char *reply1 = "$3\r\ncat\r\n";
//		printf("reply1:\n");
//		Decode(reply1);

//		char *reply2 = "$-1\r\n";
//		printf("reply2:\n");
//		Decode(reply2);
//	}

//	// 数组
//	void Test5()
//	{
//		char *reply1 = "*2\r\n$3\r\ncat\r\n$2\r\n11\r\n";
//		printf("reply1:\n");
//		Decode(reply1);

//		char *reply2 = "*2\r\n$4\r\nfish\r\n$-1\r\n";
//		printf("reply2:\n");
//		Decode(reply2);

//		char *reply3 = "*-1\r\n";
//		printf("reply3:\n");
//		Decode(reply3);
//	}
}

#endif
