
#ifndef SOCKET_MSG_H
#define SOCKET_MSG_H

#include "lib/include/thread/threadsysid.h"
#include "common/macro.h"


namespace SocketMsg
{
	// socket thread msg
	enum
	{
		STM_ADD_HANDLER = ThreadSysID::MAX_ID + 1,
		STM_ADD_HANDLER_RET,
		STM_SEND_MSG,
		STM_REMOVE_HANDLER,
		MAX_ID
	};

	struct AddHandler
	{
		int flag;
		void *listener;
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