
#include "callback.h"
#include "interface.h"

void InnerCallBack::Accept()
{
	printf("fuck accept.................\n");
}

void InnerCallBack::Recv(GameMsg *msg)
{
	//m_frame->InnerRecv(msg);
}

void InnerCallBack::Disconnect(NetHandle handle)
{
	printf("fuck disconnect.................\n");
}


void OuterCallBack::Accept()
{
	printf("fuck accept.................\n");
}

void OuterCallBack::Recv(GameMsg *msg)
{
	//m_frame->OuterRecv(msg);
}

void OuterCallBack::Disconnect(NetHandle handle)
{
	printf("fuck disconnect.................\n");
}
