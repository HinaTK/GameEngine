
#include "msgproxy.h"

void AcceptMsg::Recv(GameMsg *msg)
{
	m_call_back->Accept(msg->handle, msg->data); 
	delete msg;
}

