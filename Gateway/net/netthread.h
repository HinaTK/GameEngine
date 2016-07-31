
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
	virtual ~NetThread();
	NetThread(ThreadManager *manager, void *arg);

	struct GameServer
	{
		NetHandle		handle;
		unsigned short	type;	// ��������
		unsigned short	id;		// ����id
	};

	// ����������������
	void	InnerRecv(GameMsg *msg);
	void	InsertGame(GameMsg *msg);

	void	ConnetRet(NetHandle handle, int flag);
protected:
	bool	Init();
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	NetManager		m_net_manager;
	InnerCallBack	*m_inner_callback;
	game::Vector<GameServer> m_game_server;
};

#endif