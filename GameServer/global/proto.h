
#ifndef GLOBAL_THREAD_PROTO_H
#define GLOBAL_THREAD_PROTO_H

#include "lib/include/thread/threadsysid.h"
#include "common/serverdef.h"

namespace TProto
{
	static const unsigned char THREAD_TYPE = 2;
	enum
	{
		TO_GLOBAL_XXXX = BASE_THREAD_MSG_TYPE(THREAD_TYPE),
		TO_GLOBAL_LOAD_ROLE
	};

	enum
	{
		FROM_GLOBAL_REG_ROLE = BASE_THREAD_MSG_TYPE(THREAD_TYPE),
		FROM_GLOBAL_LOGIN
		FROM_GLOBAL_LOGOUT
	};

}

#endif