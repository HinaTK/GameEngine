
#ifndef CALL_BACK_H
#define CALL_BACK_H

#include "lib/include/frame/msgcallback.h"

class DatabaseFrame;
class InnerCallBack : public MsgCallBack
{
public:
    InnerCallBack(DatabaseFrame *frame) : m_frame(frame){}
    ~InnerCallBack(){}

    void	Accept();

    void	Recv(GameMsg *msg);

    void	Disconnect(NetHandle handle);

private:
    DatabaseFrame *m_frame;
};

#endif
