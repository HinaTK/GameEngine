
#ifndef HAND_SHAKE_TIME_EVENT_H
#define HAND_SHAKE_TIME_EVENT_H

#include "nethandler.h"
#include "socketthread.h"
#include "lib/include/base/timer.h"

class HandshakeTimeEvent : public TimeEvent
{
public:
	HandshakeTimeEvent(SocketThread *t, NetHandle handle) :m_t(t), m_handle(handle){}
	void OnTime()
	{
		ThreadNet::NET_HANDLER_ARRAY *net_handler = m_t->GetNetHandlerArray();
		ThreadNet::NET_HANDLER_ARRAY::iterator itr = net_handler->Find(m_handle);
		if (itr != net_handler->End() && (*itr)->Type() == NetHandler::HANDSHAKER)
		{
			m_t->RemoveHandler(m_handle, NetHandler::DR_HANDSHAKE_TIME_OUT);
		}
	}

	SocketThread  *m_t;
	NetHandle 	m_handle;
};

#endif

