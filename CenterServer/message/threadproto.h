
#ifndef THREAD_PROTO_H
#define THREAD_PROTO_H

#include "lib/include/frame/socketmsg.h"
#include "common/serverdef.h"

namespace ThreadProto
{
	// thread protocol
	enum
	{
		TP_LOAD_ROLE = SocketMsg::MAX_ID + 1,
	};

	struct LoadRole
	{
		PlatName	plat_name;
		ServerID	server_id;
	};
}

#endif