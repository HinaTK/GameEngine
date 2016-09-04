
#include "netthread.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/socketthread.h"
#include "lib/include/inner/innerlistener.h"
#include "lib/include/gate/gateaccepter.h"
#include "lib/include/gate/gatelistener.h"
#include "lib/include/base/function.h"

class CallBack : public MsgCallBack
{
public:
	CallBack(NetThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip){ m_thread->PushTimer(handle); };

	void	Recv(NetMsg *msg)
	{ 
		// todo 直接转到global
		//m_thread->GetManager()->SendMsg(((GateThread *)m_thread)->GetGlobal(), GateThread::GATE_ROLE_BIND, len + sizeof(NetHandle), data, m_thread->GetID());
		m_thread->Recv(msg); 
	};

	void	Disconnect(NetHandle handle, int err, int reason){}

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

	void	Accept(NetHandle handle, const char *ip){}

	void	Recv(NetMsg *msg){ m_thread->InnerRecv(msg); };

	void	Disconnect(NetHandle handle, int err, int reason){}

private:
	NetThread *m_thread;
};

NetThread::NetThread(ThreadManager *manager, int index)
: GateThread(manager)
, m_cur_thread_id(0)
, m_index(index)
, m_role_msg(1024)
{
	m_name = "net";
}

NetThread::~NetThread()
{
}

bool NetThread::Init()
{
	ServerInfo &info1 = GatawayConfig::Instance().m_server[m_index];
	if (!InitServer(info1.ip, info1.port, info1.backlog, new GateAccepter(this, 1024), new CallBack(this)))
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
		memcpy(rs.ip, info1.ip, sizeof(rs.ip));
		rs.port = info1.port;
		Send(m_cneter_handle, sizeof(PProto::tocRegisterServer), (const char *)&rs);
	}
	else return false;

	return true;
}

void NetThread::Ready()
{
	//m_manager->SendMsg(GetThreadID(), ThreadProto::TP_LOAD_ROLE_MAX_ID, 0, NULL, m_id);
}

void NetThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	
}
void NetThread::Dispatch(unsigned int msg_id, NetMsg &msg)
{
	// todo 玩家下线，需要通知gate，并将消息队列移除
	// 消息队列由GateThread delete

	if (m_role_msg.Exist(msg_id))
	{
		m_role_msg[msg_id]->Push(msg);
	}
}

unsigned int NetThread::RegRole(NetHandle handle)
{
	unsigned int index = m_role_msg.Insert(new MsgQueue<NetMsg>());
	NET_HANDLER_ARRAY::iterator itr = m_net_handler.Find(handle);
	if (itr != m_net_handler.End() && (*itr)->Type() == NetHandler::LISTENER){
		((GateListener *)(*itr))->SetMsgID(index);
	}
	else{
		Function::Error("%s can not find the handle", __FUNCTION__);
	}
	return index;
}

void NetThread::DelRole(unsigned int index)
{
	MsgQueue<NetMsg> *temp;
	if (m_role_msg.Erase(index, temp))
	{
		delete temp;
	}
}

void NetThread::ChangeChannel(NetHandle handle)
{
	NET_HANDLER_ARRAY::iterator itr = m_net_handler.Find(handle);
	if (itr != m_net_handler.End() && (*itr)->Type() == NetHandler::LISTENER)
	{
		if (((GateListener *)(*itr))->Recv == &GateListener::Bind)
		{
			((GateListener *)(*itr))->Recv = &GateListener::Dispatch;
		}
		else
		{
			Function::Error("%s the handle function is not bind", __FUNCTION__);
		}
	}
	else
	{
		Function::Error("%s handler is not a listener", __FUNCTION__);
	}
}

void NetThread::InnerRecv(NetMsg *msg)
{
	
}