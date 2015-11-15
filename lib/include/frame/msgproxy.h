
#ifndef MSG_PROXY_H
#define MSG_PROXY_H

#include "msgcallback.h"

/*
	消息代理
*/

// 用内存池
class GameMsg;
class BaseMsg
{
public:
	BaseMsg(MsgCallBack *call_back):m_call_back(call_back){}
	~BaseMsg(){}

	enum MsgType
	{
		MSG_ACCEPT = 0,
		MSG_RECV,
		MSG_DISCONNECT,
		MSG_MAX
	};

	virtual void Recv(GameMsg *msg){};
	MsgCallBack *m_call_back;
};

class AcceptMsg : public BaseMsg
{
public:
	AcceptMsg(MsgCallBack *call_back) :BaseMsg(call_back){}
	~AcceptMsg(){}

	virtual void Recv(GameMsg *msg){ m_call_back->Accept(); delete msg; }
};

class RecvMsg : public BaseMsg
{
public:
	RecvMsg(MsgCallBack *call_back) :BaseMsg(call_back){}
	~RecvMsg(){}

	virtual void Recv(GameMsg *msg){ m_call_back->Recv(msg); }
};

class DisconnectMsg : public BaseMsg
{
public:
	DisconnectMsg(MsgCallBack *call_back) :BaseMsg(call_back){}
	~DisconnectMsg(){}

	virtual void Recv(GameMsg *msg){ m_call_back->Disconnect(msg->handle); delete msg; }
};

#endif