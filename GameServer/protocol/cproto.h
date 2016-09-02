
#ifndef GAME_PROTO_H
#define GAME_PROTO_H

#include "common/macro.h"
#include "common/serverdef.h"

// 暂时不做对齐 #pragma pack(4)
namespace Proto
{
	enum
	{
		GAME_BEGIN = 0,
		CS_ENTER_GAME = 1,
		CS_CREATE_ROLE = 2,

		GAME_END = 100
	};

	struct csEnterGame
	{
		BindProto(csEnterGame, CS_LOGIN);
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