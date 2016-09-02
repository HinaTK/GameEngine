
#ifndef THREAD_PROTO_H
#define THREAD_PROTO_H

#include "lib/include/thread/threadsysid.h"

namespace TProto
{
	// 目标线程的id
	enum
	{
		GATE_REGISTER_QUEUE = ThreadSysID::TSID_MAX_ID,
	};
}

#endif