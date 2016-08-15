
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "callback.h"
#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"
#include "common/datastructure/gamevector.h"

class ThreadManager;
class SocketThread;
class NetThread : public BaseThread
{
public:
	
	NetThread(ThreadManager *manager, SocketThread *st);
	virtual ~NetThread(){}

	struct GameServer
	{
		NetHandle		handle;
		unsigned short	type;	// 服务类型
		unsigned short	id;		// 服务id
	};

	// 接收其它进程数据
	void	InnerRecv(NetMsg *msg);
protected:
	bool	Init();
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
	bool	CMD(short type, ThreadID sid, int len, const char *data);
private:
	NetManager	m_net_manager;
	NetHandle	m_server_handle;
};

#endif