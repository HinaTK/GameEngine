
#ifndef PROCESS_PROTO_H
#define PROCESS_PROTO_H

#include "macro.h"
#include "common/serverdef.h"

// 进程间通信协议

namespace PProto
{
	enum ServerType
	{
		ST_GAME = 0,
		ST_GATE,
		ST_PROXY,
		ST_MAX
	};

	enum
	{
		TOC_REGISTER_SERVER = 1,
		CTO_BROCAST_REGISTER,
		CTO_BROCAST_DISCONNECT,
	};

	// 注册服务
	struct tocRegisterServer
	{
		BindProto(TOC_REGISTER_SERVER);
		// type + id 构成每个服务的唯一标识
		unsigned short type;	// 服务类型
		unsigned short id;		// 服务id
		IP ip;
		unsigned short port;
	};

	// 广播其它服务注册
	struct ctoBrocastRegister
	{
		BindProto(CTO_BROCAST_REGISTER);
		unsigned short type;	// 服务类型
		unsigned short id;		// 服务id
		IP ip;
		unsigned short port;
	};

	struct ctoBrocastDisconnect
	{
		BindProto(CTO_BROCAST_DISCONNECT);
		unsigned short type;	// 服务类型
		unsigned short id;		// 服务id
	};

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

	// gateway to game

	struct gwgEnterScene
	{

	};
}

#endif

