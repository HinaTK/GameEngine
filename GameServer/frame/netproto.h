
#ifndef GAME_PROTO_H
#define GAME_PROTO_H

#include "common/macro.h"
#include "common/serverdef.h"

// ��һ���������ߣ��������ͻ��˵�ö�٣������������޸����ͣ��Ͳ���Ҫ�ͻ��˸���
// ��ʱ�������� #pragma pack(4)
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