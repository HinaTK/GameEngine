
#ifndef WEB_MSG_QUEUE_H
#define WEB_MSG_QUEUE_H

#include "circlequeue.h"
#include "common/systemdef.h"
#include "websocket/sendframe.h"

class WebMsgQueue
{
public:
	WebMsgQueue() : m_msg_queue(1024){}
	~WebMsgQueue(){};

	bool Push(NetID net_id, const char *msg, unsigned int length, bool mark = false)
	{
		SendFrame *m = new SendFrame(net_id, msg, length, mark);
		return m_msg_queue.Push(m);
	}

	bool IsEmpty(){ return m_msg_queue.IsEmpty(); }

	SendFrame ** Val()
	{
		return m_msg_queue.Val();
	}

private:
	CircleQueue<SendFrame *> m_msg_queue;
};


#endif