
#include "callback.h"
#include "netthread.h"

void CallBack::Accept(NetHandle handle, const char *ip)
{
    printf("fuck accept.................\n");
}

void CallBack::Recv(GameMsg *msg)
{
	//m_thread->
}

void InnerCallBack::Connect(NetHandle handle, int flag)
{
	//m_thread->ConnetRet(handle, flag);
}

void InnerCallBack::Recv(GameMsg *msg)
{
	//m_thread->InnerRecv(msg);
}

void InnerCallBack::Disconnect(NetHandle handle, int reason)
{
	printf("fuck disconnect.................\n");
}