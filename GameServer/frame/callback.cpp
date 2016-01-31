
#include "callback.h"
#include "gameframe.h"

void InnerCallBack::Accept(NetHandle handle, const char *ip)
{
    printf("fuck accept.................\n");
}

void InnerCallBack::Recv(GameMsg *msg)
{
    m_frame->InnerRecv(msg);
}

void InnerCallBack::Disconnect(NetHandle handle, int reason)
{
    printf("fuck disconnect.................\n");
}


void OuterCallBack::Accept(NetHandle handle, const char *ip)
{
    printf("fuck accept.................\n");
}

void OuterCallBack::Recv(GameMsg *msg)
{
    m_frame->OuterRecv(msg);
}

void OuterCallBack::Disconnect(NetHandle handle, int reason)
{
    printf("fuck disconnect.................\n");
}
