
#include <stdlib.h>
#include "rpcserver.h"


RPCSerializer::RPCSerializer(char *data, unsigned int length)
: Serializer(data, length)
{
	m_begin = m_begin + INT_LEN_2;
}

bool RPCSerializer::PushFront(unsigned int server_id, unsigned int msg_id)
{
	*(unsigned int *)(m_data) = server_id;
	*(unsigned int *)(m_data + INT_LEN) = msg_id;
	return true;
}

RPCServer::RPCServer()
: m_net_manager(NULL)
, m_net_handle(0)
, m_max_id(0)
, m_rpc_vector(NULL)
{

}

RPCServer::~RPCServer()
{
	if (m_rpc_vector != NULL)
	{
		free(m_rpc_vector);
		m_rpc_vector = NULL;
	}	
}

void RPCServer::Init(NetManager *net_manager, NetHandle handle, unsigned int server_id, unsigned int max_id)
{
	m_net_manager = net_manager;
	m_net_handle = handle;
	m_max_id = max_id;
	m_rpc_vector = (RPC	**)malloc(max_id * sizeof(RPC *));
	memset(m_rpc_vector, NULL, max_id * sizeof(RPC *));
}

bool RPCServer::RegisterRPC(unsigned int id, RPC *rpc)
{
	if (id >= m_max_id)
	{
		return false;
	}

	m_rpc_vector[id] = rpc;
	return true;
}

bool RPCServer::Call(unsigned int server_id, unsigned int msg_id, RPCSerializer &serializer)
{
	if (msg_id >= m_max_id)
	{
		return false;
	}

	serializer.PushFront(server_id, msg_id);
 
 	m_net_manager->Send(m_net_handle, (const char *)serializer.Data(), serializer.DataLength());
	return true;
}

bool RPCServer::CallBack(const char *data, unsigned int length)
{
	if (length < RPCSerializer::INT_LEN_2)
	{
		return false;
	}

	unsigned int id = *(unsigned int *)data;
	if (id >= m_max_id)
	{
		return false;
	}

	if (m_rpc_vector[id] == NULL)
	{
		return false;
	}

	RPCSerializer serializer((char *)data + RPCSerializer::INT_LEN_2, length - RPCSerializer::INT_LEN_2);
	m_rpc_vector[id]->CallBack(serializer);
	return true;
}

unsigned int RPCServer::GetServerID(const char *data)
{
	return *(unsigned int *)data;
}
