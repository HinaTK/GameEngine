
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
		Account	account;
		ServerID	server_id;
	};
}


#endif