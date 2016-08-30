
#include "gatethread.h"
#include "gateaccepter.h"
#include "lib/include/inner/inneraccepter.h"
#include "lib/include/inner/innerlistener.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/base/interface.h"
#include "lib/include/base/function.h"
#include "common/proto.h"
#include "common/datastructure/msgqueue.h"

class CallBack : public MsgCallBack
{
public:
	CallBack(GateThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip){};

	void	Recv(NetMsg *msg){ m_thread->Dispatch(msg); }

	void	Disconnect(NetHandle handle, int err, int reason){};

private:
	GateThread *m_thread;
};

class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(GateThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~InnerCallBack(){}

	void Accept(NetHandle handle, const char *ip)
	{
		Function::Info("accept %s", ip);
	};

	void	Recv(NetMsg *msg){};

	void	Disconnect(NetHandle handle, int err, int reason){};

private:
	GateThread *m_thread;
};

GateThread::GateThread(ThreadManager *manager, int index)
: SocketThread(manager)
, m_index(index)
, m_role_msg(2048)
{
	m_name = "gate";
}

bool GateThread::Init()
{
	ServerInfo info = GatawayConfig::Instance().m_server[m_index];
	if (!InitServer(info.ip, info.port, info.backlog, new GateAccepter(this, 1024), new CallBack(this)))
	{
		return false;
	}

	ServerInfo info2 = GameConfig::Instance().center;
	m_cneter_handle = SyncConnect(info2.ip, info2.port, new InnerListener(this), new InnerCallBack(this));
	
	if (m_cneter_handle != INVALID_NET_HANDLE)
	{
		PProto::tocRegisterServer rs;
		rs.type = PProto::ST_GATE;
		rs.id = 1;
		memcpy(rs.ip, info.ip, sizeof(rs.ip));
		rs.port = info.port;
		Send(m_cneter_handle, sizeof(PProto::tocRegisterServer), (const char *)&rs);
	}
	else return false;
	return true;
}

void GateThread::Ready()
{

}

void GateThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{

}

void GateThread::Dispatch(NetMsg *msg)
{
	ROLE_MSG::iterator itr = m_role_msg.Find(msg->handle);
	if (itr != m_role_msg.End() && itr->val != NULL)
	{
		itr->val->Push(*msg);
	}
}


EXPORT GateThread * New::_GateThread(ThreadManager *manager, int index)
{
	return new GateThread(manager, index);
}
