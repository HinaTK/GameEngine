
#include "netthread.h"
#include "callback.h"
#include "common/proto.h"
#include "lib/include/inner/inneraccepter.h"
#include "lib/include/inner/innerlistener.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/base/interface.h"

NetThread::NetThread(ThreadManager *manager)
: SocketThread(manager)
{
	m_name = "net";
}

bool NetThread::Init()
{
	ServerInfo info1 = GameConfig::Instance().game;
	if (!InitServer(info1.ip, info1.port, info1.backlog, new InnerAccepter(this), new CallBack(this))) return false;

	ServerInfo info2 = GameConfig::Instance().center;
	m_cneter_handle = SyncConnect(info2.ip, info2.port, new InnerListener(this), new InnerCallBack(this));
	
	if (m_cneter_handle != INVALID_NET_HANDLE)
	{
		ServerInfo info1 = GameConfig::Instance().game;
		PProto::tocRegisterServer rs;
		rs.type = PProto::ST_GAME;
		rs.id = 1;
		memcpy(rs.ip, info1.ip, sizeof(rs.ip));
		rs.port = info1.port;
		Send(m_cneter_handle, sizeof(PProto::tocRegisterServer), (const char *)&rs);
	}
	else return false;
	return true;
}

void NetThread::Ready()
{

}

void NetThread::RecvData(short type, ThreadID sid, int len, const char *data)
{

}

