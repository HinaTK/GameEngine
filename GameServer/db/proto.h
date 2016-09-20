
#ifndef DB_THREAD_PROTO_H
#define DB_THREAD_PROTO_H

#include "lib/include/thread/threadsysid.h"
#include "common/serverdef.h"

namespace TProto
{
	static const unsigned char THREAD_TYPE = 3;
	enum
	{
		TO_DB_LOAD_ROLE = BASE_THREAD_MSG_TYPE(THREAD_TYPE),
		
	};

	enum
	{
		R_DB_XXXX = BASE_THREAD_MSG_TYPE(THREAD_TYPE),
	};

}

#endif