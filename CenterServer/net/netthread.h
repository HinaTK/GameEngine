
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include <vector>
#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"
#include "protocol/innerproto.h"

class ThreadManager;
class NetThread : public BaseThread
{
public:
	virtual ~NetThread();
	NetThread(ThreadManager *manager);

	struct OtherServer
	{
		NetHandle handle;
		unsigned short id;
		char ip[32];
		unsigned short port;
	};
	
	// 接收其它进程数据
	void	InnerRecv(GameMsg *msg);
	void	InsertServer(GameMsg *msg);
	void	RemoveServer(NetHandle handle);
protected:
	void	Init(void *arg);
	bool	Run();
	void	RecvData(short type, int sid, int len, const char *data);
private:
	NetManager	*m_net_manager;
	std::vector<OtherServer> m_server[Inner::ST_MAX];		// 连接到中心服的其它服务

};

#endif