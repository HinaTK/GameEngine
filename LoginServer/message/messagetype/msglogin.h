
#ifndef MSGLOGIN_H
#define MSGLOGIN_H

#include "common/protocol/messagetype.h"
#include "common/protocol/messageheader.h"

namespace EProtocol
{
	struct CSUserLogin
	{
		CSUserLogin():header(EProtocol::MT_USER_LOGIN){}
		MessageHeader	header;
		unsigned int	account;
		unsigned int	password;
	};
};


#endif