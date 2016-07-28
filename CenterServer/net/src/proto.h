
#ifndef CENTER_PROTO_H
#define CENTER_PROTO_H

#include "common/macro.h"
#include "common/serverdef.h"
#include "protocol/msgid.h"

// 暂时不做对齐 #pragma pack(4)
namespace Proto
{
	struct csLogin
	{
		BindProto(csLogin, CS_LOGIN);
		Account		account;
		ServerID	sid;
	};

	struct csCreateRole
	{
		BindProto(csCreateRole, CS_CREATE_ROLE);
		Account		account;
		ServerID	sid;

		GameName	name;
	};
}


#endif