
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include "lib/include/thread/basethread.h"
#include "lib/include/frame/socketthread.h"
#include "common/datastructure/gamehash.h"

class MsgQueue;
class ThreadManager;
class NetThread : public SocketThread
{
public:
	virtual ~NetThread(){}
	NetThread(ThreadManager *manager);

protected:
	bool	Init();
	void	Ready();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:
	NetHandle		m_cneter_handle;
	game:Hash<NetHandle, MsgQueue *>	m_role_msg;	// 玩家登录到场景后，会将个人的消息队列注册到这里
};

#endif