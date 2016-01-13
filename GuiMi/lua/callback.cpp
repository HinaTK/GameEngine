
#include "callback.h"
#include "interface.h"

void XXXCallBack::Accept(NetHandle handle, const char *ip)
{
	m_interface->OnXXXAccept(handle, ip);
}

static const int NAME_LEN = 24;
void XXXCallBack::Recv(GameMsg *msg)
{
	int server_id = *(int *)msg->data;
	int begin = sizeof(int);
	char name[NAME_LEN] = { 0 };
	memcpy(name, msg->data + begin, NAME_LEN);
	begin += NAME_LEN;
	const char *buf = msg->data + begin;
	m_interface->OnXXXRecv(msg->handle, server_id, name, msg->length - begin, buf);
}

void XXXCallBack::Disconnect(NetHandle handle)
{
	m_interface->OnXXXDisconnect(handle);
}

void InnerCallBack::Accept(NetHandle handle, const char *ip)
{
	m_interface->OnInnerAccept(handle, ip);
}

void InnerCallBack::Recv(GameMsg *msg)
{
	unsigned int length = *(unsigned int *)msg->data;
	int begin = sizeof(unsigned int);
	char name[NAME_LEN] = { 0 };
	memcpy(name, msg->data + begin, NAME_LEN);
	name[NAME_LEN - 1] = 0;
	begin += NAME_LEN;
	const char *buf = msg->data + begin;
	m_interface->OnInnerRecv(msg->handle, name, length - begin, buf);

// 	size_t nsz = *(size_t *)msg->data;
// 	const char *name = msg->data + sizeof(size_t);
// 	size_t dsz = *(size_t *)(name + nsz);
// 	const char *data = msg->data + sizeof(size_t)* 2 + nsz;
// 	char test[256] = { 0 };
// 	memcpy(test, data, dsz);
// 	m_interface->OnInnerRecv(msg->handle, nsz, name, dsz, data);
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
	unsigned int length = *(unsigned int *)msg->data;
	int begin = sizeof(unsigned int);
	char name[NAME_LEN] = { 0 };
	memcpy(name, msg->data + begin, NAME_LEN);
	name[NAME_LEN - 1] = 0;
	begin += NAME_LEN;
	const char *buf = msg->data + begin;
	m_interface->OnRecv(msg->handle, name, length - begin, buf);

// 	size_t nsz = *(size_t *)msg->data;
// 	const char *name = msg->data + sizeof(size_t);
// 	size_t dsz = *(size_t *)(name + nsz);
// 	const char *data = msg->data + sizeof(size_t)* 2 + nsz;
// 	m_interface->OnRecv(msg->handle, nsz, name, dsz, data);
}

void OuterCallBack::Disconnect(NetHandle handle)
{
	m_interface->OnDisconnect(handle);
}
