
#ifndef CALL_BACK_H
#define CALL_BACK_H

#include "lib/include/frame/msgcallback.h"

class NewFrame;
class InnerCallBack : public MsgCallBack
{
public:
    InnerCallBack(NewFrame *frame) : m_frame(frame){}
    ~InnerCallBack(){}

    void	Accept();

    void	Recv(GameMsg *msg);

    void	Disconnect(NetHandle handle);

private:
    NewFrame *m_frame;
};

#endif
