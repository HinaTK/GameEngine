
#include <stdlib.h>
#include "rpcserver.h"


RPCSerializer::RPCSerializer(char *data, unsigned int length)
: Serializer(data, length)
{
	m_begin = m_begin + HEAD_LEN;
}

bool RPCSerializer::PushFront(unsigned short server_index, unsigned short msg_id)
{
	*(unsigned short *)(m_data) = server_index;
	*(unsigned short *)(m_data + SHORT_LEN) = msg_id;
	return true;
}

RPCCaller::RPCCaller(NetHandle handle, unsigned short max_msg_id)
: m_net_handle(handle)
, m_max_msg_id(max_msg_id)
{
	
}

RPCCaller::~RPCCaller()
{
	
}

RPCCallee::RPCCallee(unsigned short max_msg_id)
: m_max_msg_id(max_msg_id)
{
	m_rpcs = (RPC	**)malloc(max_msg_id * sizeof(RPC *));
	memset(m_rpcs, NULL, max_msg_id * sizeof(RPC *));
}

RPCCallee::~RPCCallee()
{
	if (m_rpcs != NULL)
	{
		::free(m_rpcs);
		m_rpcs = NULL;
	}
}

bool RPCCallee::RegisterRPC(unsigned short msg_id, RPC *rpc)
{
	if (msg_id >= m_max_msg_id)
	{
		return false;
	}

	m_rpcs[msg_id] = rpc;
	return true;
}

bool RPCCallee::OnCall(unsigned short msg_id, RPCSerializer &serializer)
{
	if (msg_id >= m_max_msg_id)
	{
		return false;
	}

	if (m_rpcs[msg_id] == NULL)
	{
		return false;
	}

	m_rpcs[msg_id]->CallBack(serializer);
	return true;
}

RPCCallerManager::~RPCCallerManager()
{
	if (m_rpc_callers != NULL)
	{
		::free(m_rpc_callers);
		m_rpc_callers = NULL;
	}
}

RPCCallerManager::RPCCallerManager()
: m_net_manager(NULL)
, m_rpc_callers(NULL)
, m_max_server_index(0)
{
	
}

void RPCCallerManager::Init(NetManager *net_manager, unsigned short max_server_index)
{
	m_net_manager = net_manager;
	m_rpc_callers = (RPCCaller **)malloc(max_server_index * sizeof(RPCCaller *));
	memset(m_rpc_callers, NULL, max_server_index * sizeof(RPCCaller *));
	m_max_server_index = max_server_index;
}

bool RPCCallerManager::RegisterRPCCaller(unsigned short server_index, RPCCaller *caller)
{
	if (server_index >= m_max_server_index)
	{
		return false;
	}

	m_rpc_callers[server_index] = caller;
	return true;
}

bool RPCCallerManager::Call(unsigned short server_index, unsigned short msg_id, RPCSerializer &serializer)
{
	if (server_index >= m_max_server_index)
	{
		return false;
	}

	if (m_rpc_callers[server_index] == NULL)
	{
		return false;
	}

	if (msg_id >= m_rpc_callers[server_index]->GetMaxMsgID())
	{
		return false;
	}

	serializer.PushFront(server_index, msg_id);
	m_net_manager->Send(m_rpc_callers[server_index]->GetNetHandle(), (const char *)serializer.Data(), serializer.DataLength());

	return true;
}

RPCCalleeManager::~RPCCalleeManager()
{
	if (m_rpc_callees != NULL)
	{
		::free(m_rpc_callees);
		m_rpc_callees = NULL;
	}
}

RPCCalleeManager::RPCCalleeManager()
: m_net_manager(NULL)
, m_rpc_callees(NULL)
, m_max_server_index(0)
{

}

void RPCCalleeManager::Init(NetManager *net_manager, unsigned short max_server_index)
{
	m_net_manager = net_manager;
	m_rpc_callees = (RPCCallee **)malloc(max_server_index * sizeof(RPCCallee *));
	memset(m_rpc_callees, NULL, max_server_index * sizeof(RPCCallee *));
	m_max_server_index = max_server_index;
}

bool RPCCalleeManager::RegisterRPCCallee(unsigned short server_index, RPCCallee *callee)
{
	if (server_index >= m_max_server_index)
	{
		return false;
	}

	m_rpc_callees[server_index] = callee;
	return true;
}

bool RPCCalleeManager::OnCall(const char *data, unsigned int length)
{
	if (length < RPCSerializer::HEAD_LEN)
	{
		return false;
	}

	unsigned short server_index = *(unsigned short *)data;
	if (server_index >= m_max_server_index)
	{
		return false;
	}

	if (m_rpc_callees[server_index] == NULL)
	{
		return false;
	}

	unsigned short msg_id = *(unsigned short *)(data + RPCSerializer::SHORT_LEN);

	RPCSerializer serializer((char *)data + RPCSerializer::HEAD_LEN, length - RPCSerializer::HEAD_LEN);
	return m_rpc_callees[server_index]->OnCall(msg_id, serializer);
}
