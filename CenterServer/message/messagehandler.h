
#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H


#include "protocol/msgid.h"

class NetThread;
class GameMsg;
class MessageHandler
{
public:
	MessageHandler(NetThread *t);
	~MessageHandler(){};

	
	void	HandleMessage(GameMsg *msg);
protected:
	typedef void (MessageHandler::*HandleFunc)(GameMsg *msg);
	struct HandlerItem 
	{
		HandlerItem():func(0), length(0){}
		HandlerItem(HandleFunc f, int s):func(f), length(s){}
		HandleFunc		func;
		unsigned short	length;
	};
	HandlerItem m_function_list[Proto::CENTER_END];
	void CSLogin(GameMsg *msg);

	NetThread *	m_thread;
};

#endif