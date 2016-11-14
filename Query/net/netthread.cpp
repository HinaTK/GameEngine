
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

    void	Recv(NetMsg *msg){m_thread->Recv(&msg);}

	void	Disconnect(NetHandle handle, int err, int reason){};

private:
	NetThread *m_thread;
};

class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(NetThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~InnerCallBack(){}

	void	Connect(NetHandle handle, int flag){};

	void	Recv(NetMsg &msg){m_thread->InnerRecv(&msg);}

	void	Disconnect(NetHandle handle, int reason){};

private:
	NetThread *m_thread;
};

NetThread::NetThread(ThreadManager *manager, int index)
: SocketThread(manager)
, m_server_handle(INVALID_NET_HANDLE)
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
	
	m_server_handle = SyncConnect("127.0.0.1", 12346, new GateListener(this), new InnerCallBack(this));
	if (m_server_handle == INVALID_NET_HANDLE)
	{
		return false;
	}
	return true;
}

void NetThread::Recv(NetMsg *msg)
{
	// 接收到初始化后，分配一个唯一id，之后在场景分配对象id，
	// 并返回给本地网关，本地网关存储后，通知客户端切换场景
	// SCSceneEnter
}

void NetThread::InnerRecv(NetMsg *msg)
{
	// 收到的数据，发送到网关
	// GWCenterSend
}

void NetThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{

}

bool NetThread::CMD(TPT type, ThreadID sid, int len, const char *data)
{
	return true;
}

