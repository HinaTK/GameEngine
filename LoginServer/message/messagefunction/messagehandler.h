
#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "common/commonvariable.h"
#include "common/protocol/messagetype.h"

class Role;

#define REAL_TYPE(type)\
	type - EProtocol::MT_LOGIN_BEGIN\

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler(){};

	
	void	HandleMessage(char * msg, UInt16 length);
protected:
	typedef void (MessageHandler::*HandleFunc)(const char *msg, UInt16 length);
	struct HandlerItem 
	{
		HandlerItem():func(0), msg_length(0){}
		HandlerItem(HandleFunc f, int s):func(f), msg_length(s){}
		HandleFunc	func;
		UInt16		msg_length;
	};
	HandlerItem m_function_list[EProtocol::MT_LOGIN_END - EProtocol::MT_LOGIN_BEGIN];
	void UserLogin(const char *msg, UInt16 length);
};

#endif