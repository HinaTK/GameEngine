
#ifndef THREAD_PROTO_H
#define THREAD_PROTO_H

#include "lib/include/frame/socketmsg.h"
#include "common/serverdef.h"

namespace ThreadProto
{
	// thread protocol
	enum
	{
		TP_LOAD_ROLE_MAX_ID = SocketMsg::MAX_ID + 1,
		TP_LOAD_ROLE_MAX_ID_RET,
		TP_LOAD_ROLE,
		TP_LOAD_ROLE_RET,
		TP_SAVE_ROLE_MAX_ID
	};

	struct LoadRole
	{
		Account		account;
		ServerID	server_id;
	};

	struct LoadRoleRet
	{
		GameName	name;
	};
}

#endif