
#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include "circlequeue.h"
#include "common/systemdef.h"
//#include "common/memoryvl.h"
#include "lib/include/frame/message.h"

class MsgQueue
{
public:
	MsgQueue() :m_msg_queue(1024){}
	~MsgQueue(){};


	bool Push(NetID net_id, const char *msg, unsigned int length)
	{
		GameMsg *m = new GameMsg(net_id, msg, length);
		return m_msg_queue.Push(m);
	}

	bool IsEmpty(){ return m_msg_queue.IsEmpty(); }

	GameMsg ** Pop()
	{
		return m_msg_queue.Pop();
	}

private:

	CircleQueue<GameMsg *> m_msg_queue;
};

#endif