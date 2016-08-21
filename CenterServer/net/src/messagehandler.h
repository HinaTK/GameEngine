
#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "proto.h"
#include "lib/include/frame/message.h"

class NetThread;
class MessageHandler
{
public:
	MessageHandler(NetThread *t);
	~MessageHandler(){};
	typedef void (MessageHandler::*HandleFunc)(NetMsg *msg);

	void	HandleMessage(NetMsg *msg);
protected:
	
	struct HandlerItem 
	{
		HandlerItem():func(0), length(0){}
		HandlerItem(HandleFunc f, int s):func(f), length(s){}
		HandleFunc		func;
		unsigned short	length;
	};
	HandlerItem m_function_list[Proto::CENTER_END];

	void	CSLogin(NetMsg *msg);
	void	CSCreateRole(NetMsg *msg);

	NetThread		*m_thread;

};

#endif