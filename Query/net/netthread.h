
#ifndef NET_THREAD_H
#define NET_THREAD_H


#include "lib/include/frame/socketthread.h"
#include "common/datastructure/gamevector.h"

class ThreadManager;
class NetThread : public SocketThread
{
public:
	
	NetThread(ThreadManager *manager, int index);
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
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
	bool	CMD(TPT type, ThreadID sid, int len, const char *data);
private:
	NetHandle	m_server_handle;
	int			m_index;
};

#endif