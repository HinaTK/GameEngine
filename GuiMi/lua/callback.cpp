
#include "callback.h"
#include "interface.h"

void XXXCallBack::Accept(NetHandle handle, const char *ip)
{
	m_interface->OnXXXAccept(handle, ip);
}


void XXXCallBack::Recv(GameMsg *msg)
{
	m_interface->OnXXXRecv(msg->handle, msg->length, msg->data);
}

void XXXCallBack::Disconnect(NetHandle handle, int reason)
{
	m_interface->OnXXXDisconnect(handle);
}

void InnerCallBack::Accept(NetHandle handle, const char *ip)
{
	m_interface->OnInnerAccept(handle, ip);
}

void InnerCallBack::Recv(GameMsg *msg)
{
	m_interface->OnInnerRecv(msg->handle, msg->length, msg->data);
	delete msg;
}

void InnerCallBack::Disconnect(NetHandle handle, int reason)
{
	m_interface->OnInnerDisconnect(handle);
}


void OuterCallBack::Accept(NetHandle handle, const char *ip)
{
	m_interface->OnAccept(handle, ip);
}

void OuterCallBack::Recv(GameMsg *msg)
{
	m_interface->OnRecv(msg->handle, msg->length, msg->data);
	delete msg;
}

void OuterCallBack::Disconnect(NetHandle handle, int reason)
{
	m_interface->OnDisconnect(handle);
}
