
#ifndef SOCKET_MSG_H
#define SOCKET_MSG_H

#include "lib/include/thread/threadsysid.h"

#define BindProto(STRUCT, ID)\
	STRUCT() :type(ID){}\
	short type;


namespace SocketMsg
{



	enum
	{
		STM_ADD_HANDLER = ThreadSysID::MAX_ID + 1,
		STM_ADD_HANDLER_RET,
		STM_SEND_MSG,
	};

	struct AddHandler
	{
		BindProto(AddHandler, STM_ADD_HANDLER);
		struct Data
		{
			int flag;
			void *listener;
		}data;
	};

	struct AddHandlerRet
	{
		BindProto(AddHandlerRet, STM_ADD_HANDLER_RET);
		struct Data
		{
			int handle;
			int flag;
		}data;
	};
}

#endif