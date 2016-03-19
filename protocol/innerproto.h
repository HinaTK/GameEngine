
#ifndef INNER_PROTO_H
#define INNER_PROTO_H

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
}

#endif // !INNER_PROTO_H
