#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "global/globalvariable.h"
#include "common/protocol/messagetype.h"

class Role;

#define REAL_TYPE(type)\
	type - EProtocol::MT_GAME_BEGIN\

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();

	

protected:
	typedef void (MessageHandler::*HandleFunc)(Role *role, char *msg);
	struct HandlerItem 
	{
		HandlerItem():func(0), msg_length(0){}
		HandlerItem(HandleFunc f, int s):func(f), msg_length(s){}
		HandleFunc		func;
		unsigned short	msg_length;
	};
	HandlerItem m_function_list[EProtocol::MT_GAME_END - EProtocol::MT_GAME_BEGIN];
	void TestFunction(Role *role, char *msg);
};

#endif