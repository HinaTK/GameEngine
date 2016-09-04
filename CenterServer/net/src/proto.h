
#ifndef CENTER_PROTO_H
#define CENTER_PROTO_H

#include "common/macro.h"
#include "common/serverdef.h"

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
		SC_LOGIN		= 0
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