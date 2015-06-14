
#ifndef RPC_SERVER_H
#define RPC_SERVER_H

#include "common/socketdef.h"
#include "lib/include/frame/netmanager.h"
#include "lib/include/common/serializer.h"

//  2���ֽڷ������� + ��2���ֽ���Ϣid
class RPCSerializer : public Serializer
{
public:
	RPCSerializer(char *data, unsigned int length);

	static const unsigned int SHORT_LEN = sizeof(unsigned short);
	static const unsigned int HEAD_LEN = 2 * SHORT_LEN;

	bool	PushFront(unsigned short server_index, unsigned short msg_id);
};


class RPC
{
public:
	RPC(){}
	~RPC(){}

	virtual void CallBack(RPCSerializer &serializer) = 0;
};

/*
	* ��server_id���͵�Զ�ˣ�Զ���ٽ�server_id���ͻ������ҵ���Ӧ��RPCServer CallBack
	* ��Arrayע��һ��RPC������Ψһ��session_id, ʵ�ֽ��̼�ͨ��
*/

class RPCCaller
{
public:
	RPCCaller(NetHandle handle, unsigned short max_msg_id);
	~RPCCaller();

	NetHandle		GetNetHandle(){ return m_net_handle; }
	unsigned short	GetMaxMsgID(){ return m_max_msg_id; }

private:
	NetHandle		m_net_handle;
	unsigned short	m_max_msg_id;
};

class RPCCallee
{
public:
	RPCCallee(unsigned short max_msg_id);
	~RPCCallee();

	bool			RegisterRPC(unsigned short msg_id, RPC *rpc);
	unsigned short	GetMaxMsgID(){ return m_max_msg_id; }
	bool			OnCall(unsigned short msg_id, RPCSerializer &serializer);

private:
	unsigned short	m_max_msg_id;
	RPC				**m_rpcs;
};

class RPCCallerManager
{
public:
	~RPCCallerManager();

	static RPCCallerManager &Instance()
	{
		static RPCCallerManager manager;
		return manager;
	}

	void		Init(NetManager *net_manager, unsigned short max_server_index);

	bool		RegisterRPCCaller(unsigned short server_index, RPCCaller *caller);

	bool		Call(unsigned short server_index, unsigned short msg_id, RPCSerializer &serializer);

private:
	RPCCallerManager();

	NetManager		*m_net_manager;
	RPCCaller		**m_rpc_callers;
	unsigned short	m_max_server_index;
};

class RPCCalleeManager
{
public:
	~RPCCalleeManager();

	static RPCCalleeManager &Instance()
	{
		static RPCCalleeManager manager;
		return manager;
	}

	void		Init(NetManager *net_manager, unsigned short max_server_index);
	bool		RegisterRPCCallee(unsigned short server_index, RPCCallee *callee);
	bool		OnCall(const char *data, unsigned int length);

private:
	RPCCalleeManager();
	NetManager		*m_net_manager;
	RPCCallee		**m_rpc_callees;
	unsigned short	m_max_server_index;
};
#endif