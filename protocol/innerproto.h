
#ifndef INNER_PROTO_H
#define INNER_PROTO_H

#include "innermsgid.h"

#define BindProto(STRUCT, ID)\
	STRUCT() :router(ID){}\
	unsigned short router;

namespace Inner
{
	// game to gateway

	// gateway收到这条协议,都会广播给所有人
	struct ggwBroadcast
	{
		int length;				// 消息长度
		char *data;				// 消息
	}; 

	// 广播给指定的人
	struct ggwBroadcastSome
	{
		int some;				// 人数
		int *handles;			// 句柄
		int length;				// 消息长度
		char *data;				// 消息
	};


	enum ServerType
	{
		ST_GAME = 0,
		ST_GATE,
		ST_MAX
	};

	// 注册服务
	struct tocRegisterServer
	{
		BindProto(tocRegisterServer, TOC_REGISTER_SERVER);
		// type + id 构成每个服务的唯一标识
		unsigned short type;	// 服务类型
		unsigned short id;		// 服务id
		char ip[32];
		unsigned short port;
	};

	// 广播其它服务注册
	struct ctoBrocastRegister
	{
		BindProto(ctoBrocastRegister, CTO_BROCAST_REGISTER);
		unsigned short type;	// 服务类型
		unsigned short id;		// 服务id
		char ip[32];
		unsigned short port;
	};
}

#endif // !INNER_PROTO_H
