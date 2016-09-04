
#ifndef THREAD_PROTO_H
#define THREAD_PROTO_H

#include "lib/include/frame/socketmsg.h"
#include "common/serverdef.h"

namespace TProto
{
	// thread protocol
	enum
	{
		TP_LOAD_ROLE_MAX_ID = ThreadSysID::TSID_MAX_ID,
		TP_LOAD_ROLE_MAX_ID_RET,
		TP_LOAD_ROLE,
		TP_LOAD_ROLE_RET,
		TP_LOAD_ROLE_NONE,
		TP_SAVE_ROLE,
		TP_SAVE_ROLE_RET,
		TP_SAVE_ROLE_MAX_ID
	};

	struct LoadRole
	{
		NetHandle	handle;
		Account		account;
		ServerID	sid;
	};

	struct LoadRoleRet
	{
		NetHandle	handle;
		RoleID		rid;
		GameName	name;
	};


	struct SaveRole
	{
		NetHandle	handle;
		Account		account;
		RoleID		rid;
		ServerID	sid;
		GameName	name;
	};

	struct SaveRoleRet
	{
		NetHandle	handle;
		RoleID		rid;
		ServerID	sid;
		GameName	name;
	};
}

#endif