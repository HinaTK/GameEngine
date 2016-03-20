
#include "netthread.h"
#include "callback.h"
#include "protocol/innerproto.h"
#include "lib/include/thread/threadmanager.h"
#include "lib/include/frame/baseaccepter.h"
#include "lib/include/frame/baselistener.h"
#include "lib/include/common/serverconfig.h"

NetThread::NetThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void NetThread::Init(void *arg)
{
	ServerInfo info1 = GameConfig::Instance().server;
	m_net_manager.InitServer(info1.ip, info1.port, info1.backlog, new BaseAccepter(&m_net_manager), new CallBack(this));

	ServerInfo info2 = GameConfig::Instance().center;
	NetHandle handle = m_net_manager.ConnectServer(info2.ip, info2.port, new BaseListener(&m_net_manager), new InnerCallBack(this));
	if (handle != INVALID_NET_HANDLE)
	{
		m_net_manager.Listen();
		Inner::RegisterServer rs;
		rs.type = Inner::ST_GAME;
		rs.id = 1;
		memcpy(rs.ip, info1.ip, sizeof(rs.ip));
		rs.port = info1.port;
		m_net_manager.Send(handle, (const char *)&rs, sizeof(Inner::RegisterServer));
	}
}


bool NetThread::Run()
{
	return m_net_manager.Update();
}

void NetThread::RecvMsg(unsigned char sid, int len, const char *data)
{

}

