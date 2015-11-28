
#include "callback.h"
#include "databaseframe.h"

void InnerCallBack::Accept()
{
    printf("fuck accept.................\n");
}

void InnerCallBack::Recv(GameMsg *msg)
{
    m_frame->Recv(msg);
}

void InnerCallBack::Disconnect(NetHandle handle)
{
    printf("fuck disconnect.................\n");
}
