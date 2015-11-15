
#ifndef MSG_CALL_BACK_H
#define MSG_CALL_BACK_H

#include "message.h"

class MsgCallBack
{
public:
	MsgCallBack(){}
	~MsgCallBack(){}

	virtual void Accept(){}

	virtual void Recv(GameMsg *msg) = 0;

	virtual void Disconnect(NetHandle handle){};
};


#endif