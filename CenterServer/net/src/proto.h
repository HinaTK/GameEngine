
#ifndef CENTER_PROTO_H
#define CENTER_PROTO_H

#include "common/macro.h"
#include "common/serverdef.h"

// 做一个导出工具，导出给客户端的枚举，这样服务器修改类型，就不需要客户端改了
// 暂时不做对齐 #pragma pack(4)
namespace Proto
{
	enum
	{
		CS_LOGIN		= 0,
		CS_CREATE_ROLE	= 1,

		CENTER_END		= 100,
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
		ServerID	sid;
	};

	struct scLogin
	{
		BindProto(SC_LOGIN);
		RoleID rid = 0;
		char ip[16];
		unsigned short port;
	};

	struct scLoginErr
	{
		BindProto(SC_LOGIN_ERR);
		enum MyEnum
		{
			LE_NO_ROLE
		};
		int result;
	};

	struct csCreateRole
	{
		BindProto(CS_CREATE_ROLE);
		Account		account;
		ServerID	sid;

		GameName	name;
	};
}


#endif