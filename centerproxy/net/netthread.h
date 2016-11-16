
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include <vector>
#include "lib/include/frame/socketthread.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"
#include "common/datastructure/gamehash.h"

class ThreadManager;
class NetThread : public SocketThread
{
public:
	
	NetThread(ThreadManager *manager, int index);
	virtual ~NetThread(){}

	struct Route
	{
		NetHandle	handle;			// 本套接字与网关的句柄
		int			gate_net_id;	// 角色在网关中对应的客户端网络id
	};

	// 接收其它进程数据
	void	Recv(NetMsg *msg);
	void	InnerRecv(NetMsg *msg);
protected:
	bool	Init();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
	bool	CMD(TPT type, ThreadID sid, int len, const char *data);

	void 	OnInnerRecv(const char *data, int length);
	void 	OnInnerRecvDisconnect(const char *data, int length);
private:
	typedef game::Array<Route>							PROXY_TO_GATE;	// 通过代理id,找到对应的网关id
	typedef std::vector<game::Hash<int, NetHandle>>		GATE_TO_PROXY;	// 通过本进程句柄和本地网关用户网络id,找到中心服的用户句柄
	NetHandle	m_server_handle;
	int			m_index;

	PROXY_TO_GATE	m_proxy;
	GATE_TO_PROXY	m_gate;

};

#endif