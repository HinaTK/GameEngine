
#ifndef CALL_BACK_H
#define CALL_BACK_H

#include "lib/include/frame/message.h"

class NetThread;
class CallBack : public MsgCallBack
{
public:
	CallBack(NetThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip);

    void	Recv(GameMsg *msg);

	void	Disconnect(NetHandle handle, int err, int reason);

private:
	NetThread *m_thread;
};

class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(NetThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~InnerCallBack(){}

	void	Accept(NetHandle handle, const char *ip);

	void	Recv(GameMsg *msg);

	void	Disconnect(NetHandle handle, int err, int reason);

private:
	NetThread *m_thread;
};

#endif
