
#include "netthread.h"
#include "callback.h"
#include "protocol/innerproto.h"
#include "lib/include/inner/inneraccepter.h"
#include "lib/include/inner/innerlistener.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/base/interface.h"

NetThread::NetThread(ThreadManager *manager, SocketThread *st)
: BaseThread(manager, ThreadManager::EXIT_NORMAL)
, m_net_manager(manager)
{
	m_name = "net";
	m_net_manager.SetThread(st);
}

bool NetThread::Init()
{
	ServerInfo info1 = GameConfig::Instance().game;
	if (!m_net_manager.InitServer(info1.ip, info1.port, info1.backlog, new InnerAccepter(m_net_manager.GetThread()), new CallBack(this))) return false;

	ServerInfo info2 = GameConfig::Instance().center;
	m_cneter_handle = m_net_manager.SyncConnect(info2.ip, info2.port, new InnerListener(m_net_manager.GetThread()), new InnerCallBack(this));
	
	return true;
}

bool NetThread::Ready()
{
	if (m_cneter_handle != INVALID_NET_HANDLE)
	{
		ServerInfo info1 = GameConfig::Instance().game;
		Inner::tocRegisterServer rs;
		rs.type = Inner::ST_GAME;
		rs.id = 1;
		memcpy(rs.ip, info1.ip, sizeof(rs.ip));
		rs.port = info1.port;
		m_net_manager.Send(m_cneter_handle, sizeof(Inner::tocRegisterServer), (const char *)&rs);
	}
	else
	{
		return false;
	}
	return true;
}

bool NetThread::Run()
{
	bool ret = m_net_manager.Update();
	return m_world_manager.Update() || ret;
}

void NetThread::RecvData(short type, ThreadID sid, int len, const char *data)
{

}

