
#include "netthread.h"
#include "callback.h"
#include "protocol/innerproto.h"
#include "lib/include/thread/threadmanager.h"
#include "lib/include/frame/baselistener.h"
#include "lib/include/common/serverconfig.h"

NetThread::NetThread(ThreadManager *manager)
: BaseThread(manager, NULL, ThreadManager::EXIT_NORMAL)
, m_net_manager(manager)
{

}

void NetThread::Init(void *arg)
{
	ServerInfo info1 = GameConfig::Instance().server;
	m_net_manager.InitServer(info1.ip, info1.port, info1.backlog, new CallBack(this));

	ServerInfo info2 = GameConfig::Instance().center;
	NetHandle handle = m_net_manager.SyncConnect(info2.ip, info2.port, new InnerCallBack(this));
	if (handle != INVALID_NET_HANDLE)
	{
		Inner::tocRegisterServer rs;
		rs.type = Inner::ST_GAME;
		rs.id = 1;
		memcpy(rs.ip, info1.ip, sizeof(rs.ip));
		rs.port = info1.port;
		m_net_manager.Send(handle, sizeof(Inner::tocRegisterServer), (const char *)&rs);
	}
}


bool NetThread::Run()
{
	bool ret = m_net_manager.Update();
	ret = m_world_manager.Update() && ret;
	return ret;
}

void NetThread::RecvData(short type, int sid, int len, const char *data)
{

}

