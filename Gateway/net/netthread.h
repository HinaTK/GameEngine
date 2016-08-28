
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "callback.h"
#include "lib/include/frame/socketthread.h"
#include "common/datastructure/gamevector.h"

class ThreadManager;
class NetThread : public SocketThread
{
public:
	virtual ~NetThread();
	NetThread(ThreadManager *manager, int index);

	struct GameServer
	{
		NetHandle		handle;
		unsigned short	type;	// 服务类型
		unsigned short	id;		// 服务id
	};

	// 接收其它进程数据
	void	InnerRecv(NetMsg *msg);
	void	InsertGame(NetMsg *msg);

	void	ConnetRet(NetHandle handle, int flag);
protected:
	bool	Init();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:
	int		m_index;
	InnerCallBack	*m_inner_callback;
	game::Vector<GameServer> m_game_server;
};

#endif