
#ifndef CENTER_PROTO_H
#define CENTER_PROTO_H

#include "common/macro.h"
#include "common/serverdef.h"
#include "protocol/msgid.h"

// ��ʱ�������� #pragma pack(4)
namespace Proto
{
	struct csLogin
	{
		BindProto(csLogin, CS_LOGIN);
		PlatName	plat_name;
		ServerID	server_id;
	};
}


#endif