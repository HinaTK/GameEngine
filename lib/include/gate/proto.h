
#ifndef GATE_THREAD_PROTO_H
#define GATE_THREAD_PROTO_H

#include "lib/include/thread/threadsysid.h"
#include "common/serverdef.h"

namespace TProto
{
	static const unsigned char THREAD_TYPE = 1;
	enum
	{
		S_GATE_REG_ROLE = BASE_THREAD_MSG_TYPE(THREAD_TYPE),
	};

	enum
	{
		R_GATE_DEL_ROLE = BASE_THREAD_MSG_TYPE(THREAD_TYPE)
	};

	struct sGateRegRole
	{
		void *queue;
		ThreadID		gate_id;
		NetHandle		handle;
		unsigned int	index;
	}; 
}

#endif