
#include "netthread.h"
#include "callback.h"
#include "lib/include/frame/baseaccepter.h"

NetThread::NetThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void NetThread::Init()
{
 	CallBack *call = new CallBack(this);
 	m_net_manager.InitServer("127.0.0.1", 2345, 16, new BaseAccepter(&m_net_manager), call);

	NetManager *net = new NetManager();
	net->InitServer("127.0.0.1", 2346, 16, new BaseAccepter(net), call);
}


bool NetThread::Run()
{

	return m_net_manager.Update();
}

void NetThread::RecvMsg(unsigned char sid, int len, const char *data)
{

}

