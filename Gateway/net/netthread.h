
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "callback.h"
#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"
#include "common/datastructure/gamevector.h"

class ThreadManager;
class NetThread : public BaseThread
{
public:
	virtual ~NetThread(){}
	NetThread(ThreadManager *manager, void *arg);

	struct GameServer
	{
		NetHandle		handle;
		unsigned short	type;	// 服务类型
		unsigned short	id;		// 服务id
	};

	// 接收其它进程数据
	void	InnerRecv(GameMsg *msg);
	void	InsertGame(GameMsg *msg);

protected:
	void	Init(void *arg);
	bool	Run();
	void	RecvData(short type, int sid, int len, const char *data);
private:
	NetManager	m_net_manager;
	game::Vector<GameServer> m_game_server;

	CallBack		m_callback;
	InnerCallBack	m_inner_callback;
};

#endif