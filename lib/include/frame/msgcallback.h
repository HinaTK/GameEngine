
#ifndef MSG_CALL_BACK_H
#define MSG_CALL_BACK_H

#include "message.h"

class MsgCallBack
{
public:
	MsgCallBack(){}
	~MsgCallBack(){}

	virtual void Accept(NetHandle handle, const char *ip) = 0;

	virtual void Recv(GameMsg *msg) = 0;

	virtual void Disconnect(NetHandle handle, int reason)= 0;
};


#endif