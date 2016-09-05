
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "lib/include/frame/socketthread.h"
#include "common/datastructure/gamevector.h"

class ThreadManager;
class NetThread : public SocketThread
{
public:
	
	NetThread(ThreadManager *manager);
	virtual ~NetThread(){}

	struct GameServer
	{
		NetHandle		handle;
		unsigned short	type;	// 服务类型
		unsigned short	id;		// 服务id
	};

	// 接收其它进程数据
	void	InnerRecv(NetMsg *msg);
	NetHandle 	GetServerHandle(){return m_server_handle;}
	void	SetServerHandle(NetHandle handle){m_server_handle = handle;}
protected:
	bool	Init();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
	bool	CMD(TPT type, ThreadID sid, int len, const char *data);
private:
	NetHandle	m_server_handle;
};

#endif