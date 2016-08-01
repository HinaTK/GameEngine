
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
		TP_SAVE_ROLE,
		TP_SAVE_ROLE_RET,
		TP_SAVE_ROLE_MAX_ID
	};

	struct LoadRole
	{
		int			handle;
		Account		account;
		ServerID	sid;
	};

	struct LoadRoleRet
	{
		int			handle;
		GameName	name;
	};

	struct SaveRole
	{
		int			handle;
		Account		account;
		RoleID		rid;
		ServerID	sid;
		GameName	name;
	};

	struct SaveRoleRet
	{
		int			handle;
		RoleID		rid;
		ServerID	sid;
		GameName	name;
	};
}

#endif