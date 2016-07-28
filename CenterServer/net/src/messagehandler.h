
#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "loginmanager.h"
#include "proto.h"
#include "protocol/msgid.h"
#include "lib/include/frame/message.h"

class NetThread;
class MessageHandler
{
public:
	MessageHandler(NetThread *t);
	~MessageHandler(){};
	typedef void (MessageHandler::*HandleFunc)(GameMsg *msg);

	void	HandleMessage(GameMsg *msg);
protected:
	
	struct HandlerItem 
	{
		HandlerItem():func(0), length(0){}
		HandlerItem(HandleFunc f, int s):func(f), length(s){}
		HandleFunc		func;
		unsigned short	length;
	};
	HandlerItem m_function_list[Proto::CENTER_END];

	void	CSLogin(GameMsg *msg){ m_login_manager->OnLogin((Proto::csLogin *)msg->data); }
	void	CSCreateRole(GameMsg *msg){ m_login_manager->OnCreateRole((Proto::csCreateRole *)msg->data); }

	NetThread		*m_thread;
	LoginManager	*m_login_manager;

};

#endif