
#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "lib/include/frame/message.h"
#include "common/protocol/internaltype.h"
#include "common/datastructure/circlequeue.h"
#include "lib/include/common/thread.h"

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();

	void	HandleMessage(GameMsg *msg);
	void	Exit();
	void	Wait();

	CircleQueue<GameMsg *> &DataQueue(){ return m_queue; }
	bool	m_is_run;
protected:
	typedef void (MessageHandler::*HandleFunc)(char *msg);
	struct HandlerItem 
	{
		HandlerItem():func(0), msg_length(0){}
		HandlerItem(HandleFunc f, int s):func(f), msg_length(s){}
		HandleFunc		func;
		unsigned short	msg_length;
	};
	HandlerItem m_function_list[IProtocol::MT_MAX_DATABASE_SERVER_TYPE - IProtocol::MT_MIN_DATABASE_SERVER_TYPE];

	CircleQueue<GameMsg *>	m_queue;
	Thread					m_flush_thread;		// 冲刷队列线程

	void	UserLogin(char * msg);
	void	Test(char *msg);
	
};

#endif