
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
		Account		account;
		ServerID	server_id;
	};
}

#endif