
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
	
	NetThread(ThreadManager *manager);
	virtual ~NetThread(){}

	struct GameServer
	{
		NetHandle		handle;
		unsigned short	type;	// ��������
		unsigned short	id;		// ����id
	};

	// ����������������
	void	InnerRecv(GameMsg *msg);
protected:
	void	Init(void *arg);
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	NetManager	m_net_manager;
};

#endif