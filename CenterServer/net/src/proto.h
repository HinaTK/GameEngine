
#ifndef CENTER_PROTO_H
#define CENTER_PROTO_H

#include "common/macro.h"
#include "common/serverdef.h"

// ��ʱ�������� #pragma pack(4)
namespace Proto
{
	enum
	{
		CENTER_BEGIN = 0,
		CS_LOGIN = 1,
		CS_CREATE_ROLE = 2,

		CENTER_END = 100,
	};

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