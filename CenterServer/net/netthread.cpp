
#include "netthread.h"
#include "callback.h"
#include "lib/include/frame/baseaccepter.h"
#include "lib/include/common/serverconfig.h"

NetThread::NetThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void NetThread::Init(void *arg)
{
	ServerInfo info1 = CenterConfig::Instance().login;
	m_net_manager.InitServer(info1.ip, info1.port, info1.backlog, new BaseAccepter(&m_net_manager), new CallBack(this));

	ServerInfo info2 = CenterConfig::Instance().center;
	m_net_manager.InitServer(info2.ip, info2.port, info2.backlog, new BaseAccepter(&m_net_manager), new InnerCallBack(this));
}


bool NetThread::Run()
{
	return m_net_manager.Update();
}

void NetThread::RecvMsg(unsigned char sid, int len, const char *data)
{

}

