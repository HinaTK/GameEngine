
#ifndef DB_THREAD_PROTO_H
#define DB_THREAD_PROTO_H

#include "lib/include/thread/threadsysid.h"
#include "common/serverdef.h"

// 只枚举对外发送的协议

namespace TProto
{
	static const unsigned char THREAD_TYPE = 3;
	enum
	{
		DB_LOAD_ROLE = BASE_THREAD_MSG_TYPE(THREAD_TYPE),
		
	};
}

#endif