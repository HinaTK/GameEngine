#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

//#include "commonvariable.h"
#include "common/protocol/internaltype.h"


class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler(){};

	void	HandleMessage(char * msg);
protected:
	typedef void (MessageHandler::*HandleFunc)(char *msg);
	struct HandlerItem 
	{
		HandlerItem():func(0), msg_length(0){}
		HandlerItem(HandleFunc f, int s):func(f), msg_length(s){}
		HandleFunc		func;
		unsigned short	msg_length;
	};
	HandlerItem m_function_list[IProtocol::MT_MSG_END];

	void	UserLogin(char * msg);

	void	Test(char *msg);
	
};

#endif