
#ifndef GAME_PROTO_H
#define GAME_PROTO_H

#include "common/macro.h"
#include "common/serverdef.h"

// 做一个导出工具，导出给客户端的枚举，这样服务器修改类型，就不需要客户端改了
// 暂时不做对齐 #pragma pack(4)
namespace Proto
{
	enum
	{
		CS_LOGIN		= 0,

		GAME_END		= 100,
	};

	enum
	{
		SC_LOGIN		= 0,
		SC_LOGIN_ERR	= 1
	};

	struct csLogin
	{
		BindProto(CS_LOGIN);
		Account		account;
		RoleID		rid;
		Session		session;
	};
}


#endif