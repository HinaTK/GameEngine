
#include "netthread.h"
#include "callback.h"
#include "main/gateway.h"
#include "lib/include/frame/baseaccepter.h"
#include "lib/include/common/serverconfig.h"

NetThread::NetThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void NetThread::Init()
{
	ServerInfo info = GatawayConfig::Instance().m_server[m_id];
	m_net_manager.InitServer(info.ip, info.port, info.backlog, new BaseAccepter(&m_net_manager), new CallBack(this));
}


bool NetThread::Run()
{

	return m_net_manager.Update();
}

void NetThread::RecvMsg(unsigned char sid, int len, const char *data)
{

}

