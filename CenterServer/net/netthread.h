
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include <vector>
#include "src/idpool.h"
#include "src/messagehandler.h"
#include "common/proto.h"
#include "lib/include/gate/gatethread.h"


class ThreadManager;
class NetThread : public GateThread
{
public:
	virtual ~NetThread();
	NetThread(ThreadManager *manager);

	struct OtherServer
	{
		NetHandle handle;
		unsigned short id;
		IP ip;
		unsigned short port;
	};
	void	Recv(NetMsg *msg){ m_message_handler.HandleMessage(msg); };

	// 接收其它进程数据
	void	InnerRecv(NetMsg *msg);
	void	InsertServer(NetMsg *msg);
	void	RemoveServer(NetHandle handle);

	IDPool			*GetIDPool(){ return &m_id_pool; }
	ThreadID 	GetThreadID();

	OtherServer *GetGate();
protected:
	bool	Init();
	void	Ready();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:
	
	std::vector<OtherServer> m_server[PProto::ST_MAX];		// 连接到中心服的其它服务
	MessageHandler	m_message_handler;
	IDPool			m_id_pool;
	ThreadID 		m_cur_thread_id;
	unsigned int 	m_gate_index;
};

#endif