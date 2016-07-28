
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include <vector>
#include "src/loginmanager.h"
#include "src/idpool.h"
#include "src/messagehandler.h"
#include "protocol/innerproto.h"
#include "lib/include/thread/basethread.h"
#include "lib/include/frame/netmanager.h"


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
	void	Recv(GameMsg *msg){ m_message_handler.HandleMessage(msg); };

	// 接收其它进程数据
	void	InnerRecv(GameMsg *msg);
	void	InsertServer(GameMsg *msg);
	void	RemoveServer(NetHandle handle);

	LoginManager	*GetLoginManager(){ return &m_login_manager; }
	IDPool			*GetIDPool(){ return &m_id_pool; }
	ThreadID 	GetThreadID();
protected:
	bool	Init();
	bool	Ready();
	bool	Run();
	void	RecvData(short type, ThreadID sid, int len, const char *data);
private:
	NetManager	*m_net_manager;
	std::vector<OtherServer> m_server[Inner::ST_MAX];		// 连接到中心服的其它服务

	MessageHandler	m_message_handler;
	LoginManager	m_login_manager;
	IDPool			m_id_pool;
	ThreadID 		m_cur_thread_id;

};

#endif