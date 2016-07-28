
#ifndef PROTO_MSG_ID_H
#define PROTO_MSG_ID_H

namespace Proto
{
	//client to server
	enum
	{
		CENTER_BEGIN = 0,
		CS_LOGIN = 1,
		CS_CREATE_ROLE = 2,

		CENTER_END = 100,
		GAME_BEGIN = 100,

		CS_PROTO_MAX
	};

	// server to client
	enum
	{

	};
}
#endif