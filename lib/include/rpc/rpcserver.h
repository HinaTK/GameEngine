
#ifndef RPC_SERVER_H
#define RPC_SERVER_H

#include "common/systemdef.h"
#include "lib/include/frame/netmanager.h"
#include "lib/include/common/serializer.h"

// 用4个字节保存协议id + 4个字节保留位
class RPCSerializer : public Serializer
{
public:
	RPCSerializer(char *data, unsigned int length);

	static const unsigned int INT_LEN = sizeof(unsigned int);
	static const unsigned int INT_LEN_2 = INT_LEN + INT_LEN;

	bool	PushFront(unsigned int server_id, unsigned int msg_id);
};


class RPC
{
public:
	RPC(){}
	~RPC(){}

	virtual void CallBack(RPCSerializer &serializer) = 0;
};


class RPCServer
{
public:
	RPCServer();
	~RPCServer();

	void		Init(NetManager *net_manager, NetHandle handle, unsigned int max_id);

	bool		RegisterRPC(unsigned int id, RPC *rpc);

	bool		Call(unsigned int server_id, unsigned int msg_id, RPCSerializer &serializer);

	bool		CallBack(const char *data, unsigned int length);

	static unsigned int GetServerID(const char *data);

private:
	
	NetManager		*m_net_manager;
	NetHandle		m_net_handle;
	unsigned int	m_max_id;
	RPC				**m_rpc_vector;
};
#endif