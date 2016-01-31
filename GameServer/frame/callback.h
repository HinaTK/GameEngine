
#ifndef CALL_BACK_H
#define CALL_BACK_H

#include "lib/include/frame/msgcallback.h"

class NewFrame;
class InnerCallBack : public MsgCallBack
{
public:
    InnerCallBack(NewFrame *frame) 
		: MsgCallBack()
		, m_frame(frame){}
    ~InnerCallBack(){}

	void	Accept(NetHandle handle, const char *ip);

    void	Recv(GameMsg *msg);

	void	Disconnect(NetHandle handle, int reason);

private:
    NewFrame *m_frame;
};

class OuterCallBack : public MsgCallBack
{
public:
    OuterCallBack(NewFrame *frame)
		: MsgCallBack()
		, m_frame(frame){}
    ~OuterCallBack(){}

	void	Accept(NetHandle handle, const char *ip);

    void	Recv(GameMsg *msg);

    void	Disconnect(NetHandle handle, int reason);

private:
    NewFrame *m_frame;
};

#endif
