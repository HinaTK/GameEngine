
#ifndef GLOBAL_THREAD_PROTO_H
#define GLOBAL_THREAD_PROTO_H

#include "lib/include/thread/threadsysid.h"
#include "common/serverdef.h"

namespace TProto
{
	enum
	{
		GLOBAL_REG_ROLE = 0,
		GLOBAL_LOAD_ROLE,
		GLOBAL_ROLE_LOGOUT,
	};
}

#endif