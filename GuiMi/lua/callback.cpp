
#include "callback.h"
#include "interface.h"

void InnerCallBack::Accept()
{
	printf("fuck accept.................\n");
}

void InnerCallBack::Recv(GameMsg *msg)
{
	//m_frame->InnerRecv(msg);
	int nsz = *(int *)msg->data;
	m_interface->OnInnerRecv(msg->handle, msg->data + sizeof(int), msg->data + sizeof(int)* 2 + nsz);
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
	//m_interface->OnRecv()
}

void OuterCallBack::Disconnect(NetHandle handle)
{
	printf("fuck disconnect.................\n");
}
