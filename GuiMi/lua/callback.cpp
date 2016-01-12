
#include "callback.h"
#include "interface.h"

void InnerCallBack::Accept(NetHandle handle, const char *ip)
{
	m_interface->OnInnerAccept(handle, ip);
}

void InnerCallBack::Recv(GameMsg *msg)
{
	size_t nsz = *(size_t *)msg->data;
	const char *name = msg->data + sizeof(int);
	size_t dsz = *(size_t *)(name + nsz);
	const char *data = msg->data + sizeof(size_t)* 2 + nsz;
	m_interface->OnInnerRecv(msg->handle, nsz, name, dsz, data);
}

void InnerCallBack::Disconnect(NetHandle handle)
{
	m_interface->OnInnerDisconnect(handle);
}


void OuterCallBack::Accept(NetHandle handle, const char *ip)
{
	m_interface->OnAccept(handle, ip);
}

void OuterCallBack::Recv(GameMsg *msg)
{
	size_t nsz = *(size_t *)msg->data;
	const char *name = msg->data + sizeof(int);
	size_t dsz = *(size_t *)(name + nsz);
	const char *data = msg->data + sizeof(size_t)* 2 + nsz;
	m_interface->OnRecv(msg->handle, nsz, name, dsz, data);
}

void OuterCallBack::Disconnect(NetHandle handle)
{
	m_interface->OnDisconnect(handle);
}
