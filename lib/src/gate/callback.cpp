
#include "callback.h"
#include "gatethread.h"

void CallBack::Accept(NetHandle handle, const char *ip)
{
    printf("fuck accept.................\n");
}

void CallBack::Recv(NetMsg *msg)
{
	//m_thread->
}

void CallBack::Disconnect(NetHandle handle, int err, int reason)
{
    printf("fuck disconnect.................\n");
}

void InnerCallBack::Accept(NetHandle handle, const char *ip)
{
	printf("fuck accept.................\n");
}

void InnerCallBack::Recv(NetMsg *msg)
{
	//m_thread->
}

void InnerCallBack::Disconnect(NetHandle handle, int err, int reason)
{
	printf("fuck disconnect %d %d .................\n", err, reason);
}

