
#include "netthread.h"
#include "protocol/innerproto.h"
#include "lib/include/frame/baseaccepter.h"
#include "lib/include/frame/baselistener.h"
#include "lib/include/common/serverconfig.h"
#include "CenterServer/message/proto.h"

NetThread::NetThread(ThreadManager *manager)
: BaseThread(manager, NULL, ThreadManager::EXIT_NORMAL)
, m_net_manager(manager)
{

}

void NetThread::Init(void *arg)
{
	NetHandle handle = m_net_manager.SyncConnect("127.0.0.1", 12347, new CallBack(this));
	Proto::csLogin login;
	memcpy(login.account, "aabbcc", sizeof("aabbcc"));
	login.server_id = 123;

	m_net_manager.Send(handle, sizeof(Proto::csLogin), (const char *)&login);
}

void NetThread::InnerRecv(GameMsg *msg)
{
}


bool NetThread::Run()
{
	return m_net_manager.Update();
}

void NetThread::RecvData(short type, ThreadID sid, int len, const char *data)
{

}

