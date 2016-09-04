
#ifndef CALL_BACK_H
#define CALL_BACK_H

#include "global.h"
#include "lib/include/common/message.h"


class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(Global *t)
		: MsgCallBack()
		, m_thread(t){}
	~InnerCallBack(){}

	void	Accept(NetHandle handle, const char *ip);

	void	Recv(NetMsg *msg){};

	void	Disconnect(NetHandle handle, int err, int reason);

private:
	Global *m_thread;
};

#endif
