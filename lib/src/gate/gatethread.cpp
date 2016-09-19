
#include "gatethread.h"
#include "gateaccepter.h"
#include "gatehandshake.h"
#include "gatelistener.h"
#include "proto.h"
#include "lib/include/frame/handshake.h"
#include "lib/include/base/interface.h"
#include "lib/include/base/function.h"
#include "lib/include/base/timer.h"
#include "lib/include/inner/innerlistener.h"
#include "common/proto.h"
#include "common/datastructure/msgqueue.h"

class CallBack : public MsgCallBack
{
public:
	CallBack(GateThread *t): MsgCallBack(), m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip){ m_thread->PushTimer(handle); };

	void	Recv(NetMsg *msg)
	{ 
		// todo 直接转到global
		//m_thread->GetManager()->SendMsg(((GateThread *)m_thread)->GetGlobal(), GateThread::GATE_ROLE_BIND, len + sizeof(NetHandle), data, m_thread->GetID());
		//m_thread->Recv(msg); 
	};

	void 	Other(NetMsg *msg)
	{
		OtherMsgType type = *((OtherMsgType *)msg->data);
		if (type == 1)
		{
			m_thread->RegRole(msg->handle);
		}
	}

	void	Disconnect(NetHandle handle, int err, int reason){}

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

	void	Accept(NetHandle handle, const char *ip){}

	void	Recv(NetMsg *msg){ /*m_thread->InnerRecv(msg); */};

	void	Disconnect(NetHandle handle, int err, int reason){}

private:
	GateThread *m_thread;
};

GateThread::GateThread(ThreadManager *manager, unsigned char index, ThreadID login_id)
: SocketThread(manager)
, m_timer_queue(New::_TimerQueue(4))
, m_index(index)
, m_login_id(login_id)
{
	m_name = "gate";
}

GateThread::~GateThread()
{
	Delete::_TimerQueue(m_timer_queue);
}

bool GateThread::Init()
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

void GateThread::Ready()
{

}

void GateThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case TProto::R_GATE_LOGOUT:
	{
		NetHandle handle = *(NetHandle *)data;
		RemoveHandler(handle);
		//DelRole(index);
		break;
	}	
	default:
		break;
	}
}

bool GateThread::DoSomething()
{
	return m_timer_queue->Update(time(NULL));
}

void GateThread::PushTimer(NetHandle handle)
{
	m_timer_queue->AddEvent(new HandshakeTimeEvent(this, handle));
}

void GateThread::RegRole(NetHandle handle)
{
	MsgQueue<NetMsg> *queue = new MsgQueue<NetMsg>();
	unsigned int index = m_role_msg.Insert(queue);
	NET_HANDLER_ARRAY::iterator itr = m_net_handler.Find(handle);
	if (itr != m_net_handler.End() && (*itr)->Type() == NetHandler::LISTENER){
		((GateListener *)(*itr))->SetMsgID(index);
	}
	else{
		Function::Error("%s can not find the handle", __FUNCTION__);
		m_role_msg.Erase(index);
		delete queue;
		return;
	}
	m_manager->SendMsg(m_login_id, TProto::S_GATE_REG_ROLE, sizeof(TProto::sGateRegRole), (const char *)&(TProto::sGateRegRole{queue, m_id, handle, index}), m_id);
}

void GateThread::DelRole(unsigned int index)
{
	MsgQueue<NetMsg> *temp;
	if (m_role_msg.Erase(index, temp))
	{
		delete temp;
	}
	// todo 通知玩家？

}

void GateThread::Dispatch(unsigned int msg_id, NetMsg &msg)
{
	// todo 跨线程（异步） NetMsg 的buf需要处理一下
	ROLE_MSG::iterator itr = m_role_msg.Find(msg_id);
	if (itr != m_role_msg.End())
	{
		(*itr)->Push(msg);
	}
	else
	{
		// out put error
	}
}

void GateThread::Dispatch(unsigned int msg_id, NetHandle handle, unsigned short len, char *data)
{
	NetMsg msg;
	msg.Alloc(handle, len, data);
	ROLE_MSG::iterator itr = m_role_msg.Find(msg_id);
	if (itr != m_role_msg.End())
	{
		(*itr)->Push(msg);
	}
	else
	{
		// out put error
	}
}