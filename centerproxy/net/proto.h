
#ifndef GATE_THREAD_PROTO_H
#define GATE_THREAD_PROTO_H

#include "lib/include/thread/threadsysid.h"
#include "common/serverdef.h"

namespace TProto
{
	enum
	{
		GATE_LOGOUT = 0
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