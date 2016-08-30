
#ifndef CALL_BACK_H
#define CALL_BACK_H

#include "lib/include/frame/message.h"

class GateThread;
class CallBack : public MsgCallBack
{
public:
	CallBack(GateThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip);

    void	Recv(NetMsg *msg);

	void	Disconnect(NetHandle handle, int err, int reason);

private:
	GateThread *m_thread;
};

class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(GateThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~InnerCallBack(){}

	void	Accept(NetHandle handle, const char *ip);

	void	Recv(NetMsg *msg);

	void	Disconnect(NetHandle handle, int err, int reason);

private:
	GateThread *m_thread;
};

#endif
