
#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "netproto.h"
#include "lib/include/common/message.h"

class TempRole;
class Role;
class Global;
class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler(){};
	typedef void (MessageHandler::*HandleFunc)(Role *role, NetMsg &msg);

	void	BeforeMessage(Global *global, TempRole *role, NetMsg &msg);
	bool	HandleMessage(Role *role, NetMsg &msg);
protected:
	
	struct HandlerItem 
	{
		HandlerItem():func(0), length(0){}
		HandlerItem(HandleFunc f, int s):func(f), length(s){}
		HandleFunc		func;
		unsigned short	length;
	};
	HandlerItem m_function_list[Proto::GAME_END];

	void	CSLogin(Global *global, TempRole *role, NetMsg &msg);

	

};

#endif