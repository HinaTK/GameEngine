
#include "netthread.h"
#include "lib/include/gate/gateaccepter.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/common/argsplit.h"
#include "lib/include/base/interface.h"
#include "CenterServer/net/src/proto.h"

class CallBack : public MsgCallBack
{
public:
	CallBack(NetThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip){};

    void	Recv(NetMsg *msg){};

	void	Disconnect(NetHandle handle, int err, int reason){};

private:
	NetThread *m_thread;
};


NetThread::NetThread(ThreadManager *manager, int index)
: SocketThread(manager)
, m_index(index)
{
	m_name = "net";
}

bool NetThread::Init()
{
	ServerInfo &info1 = ProxyConfig::Instance().proxy;
	if (!InitServer(info1.ip, info1.port, info1.backlog, new GateAccepter(this), new CallBack(this)))
	{
		return false;
	}
	

	return true;
}

void NetThread::InnerRecv(NetMsg *msg)
{
}

void NetThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{

}

bool NetThread::CMD(TPT type, ThreadID sid, int len, const char *data)
{
	return true;
}

