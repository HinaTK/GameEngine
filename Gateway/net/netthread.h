
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"
#include "common/datastructure/gamevector.h"

class ThreadManager;
class NetThread : public BaseThread
{
public:
	virtual ~NetThread(){}
	NetThread(ThreadManager *manager);

	struct GameServer
	{
		NetHandle		handle;
		unsigned short	type;	// ��������
		unsigned short	id;		// ����id
	};

	// ����������������
	void	InnerRecv(GameMsg *msg);
	void	InsertGame(GameMsg *msg);

protected:
	void	Init(void *arg);
	bool	Run();
	void	RecvMsg(unsigned char sid, int len, const char *data);
private:
	NetManager	m_net_manager;
	game::Vector<GameServer> m_game_server;
};

#endif