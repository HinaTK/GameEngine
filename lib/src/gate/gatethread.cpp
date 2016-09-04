
#include "gatethread.h"
#include "gateaccepter.h"
#include "gatelistener.h"
#include "lib/include/base/interface.h"
#include "lib/include/base/function.h"
#include "lib/include/base/timer.h"
#include "common/proto.h"
#include "common/datastructure/msgqueue.h"

class CallBack : public MsgCallBack
{
public:
	CallBack(GateThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip)
	{
		m_thread->PushTimer(handle);
	};

	void	Recv(NetMsg *msg){ }

	void	Disconnect(NetHandle handle, int err, int reason){};

private:
	GateThread *m_thread;
};

class HandshakeTimeEvent : public TimeEvent
{
public:
	HandshakeTimeEvent(GateThread *t, NetHandle handle) :m_t(t), m_handle(handle){}
	void OnTime()
	{
		ThreadNet::NET_HANDLER_ARRAY *net_handler = m_t->GetNetHandlerArray();
		ThreadNet::NET_HANDLER_ARRAY::iterator itr = net_handler->Find(m_handle);
		if (itr != net_handler->End() && (*itr)->Type() == NetHandler::LISTENER)
		{
			GateListener *listener = (GateListener *)(*itr);
			if (!listener->IsHandshake())
			{
				m_t->RemoveHandler(m_handle, NetHandler::DR_HANDSHAKE_TIME_OUT);
			}
		}
	}

	GateThread  *m_t;
	NetHandle 	m_handle;
};

GateThread::GateThread(ThreadManager *manager)
: SocketThread(manager)
, m_role_msg(1024)
//, m_global(global)
, m_timer_queue(New::_TimerQueue(4))
{
	m_name = "gate";
}

GateThread::~GateThread()
{
	delete m_timer_queue;
}

bool GateThread::Init()
{
	return true;
//	return m_gate_init->Init(this);
// 	ServerInfo info = GatawayConfig::Instance().m_server[m_index];
// 	if (!InitServer(info.ip, info.port, info.backlog, new GateAccepter(this, 1024), new CallBack(this)))
// 	{
// 		return false;
// 	}

// 	ServerInfo info2 = GameConfig::Instance().center;
// 	m_cneter_handle = SyncConnect(info2.ip, info2.port, new InnerListener(this), new InnerCallBack(this));
// 	
// 	if (m_cneter_handle != INVALID_NET_HANDLE)
// 	{
// 		PProto::tocRegisterServer rs;
// 		rs.type = PProto::ST_GATE;
// 		rs.id = 1;
// 		memcpy(rs.ip, info.ip, sizeof(rs.ip));
// 		rs.port = info.port;
// 		Send(m_cneter_handle, sizeof(PProto::tocRegisterServer), (const char *)&rs);
// 	}
// 	else return false;
//	return true;
}

void GateThread::Ready()
{

}

void GateThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	
}

bool GateThread::DoSomething()
{
	return m_timer_queue->Update(time(NULL));
}

void GateThread::Dispatch(unsigned int msg_id, NetMsg &msg)
{
	// todo 玩家下线，需要通知gate，并将消息队列移除
	// 消息队列由GateThread delete

	if (m_role_msg.Exist(msg_id))
	{
		m_role_msg[msg_id]->Push(msg);
	}
}

unsigned int GateThread::RegRole(NetHandle handle)
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

void GateThread::DelRole(unsigned int index)
{
	MsgQueue<NetMsg> *temp;
	if (m_role_msg.Erase(index, temp))
	{
		delete temp;
	}
}

void GateThread::ChangeChannel(NetHandle handle)
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

void GateThread::PushTimer(NetHandle handle)
{
	m_timer_queue->AddEvent(new HandshakeTimeEvent(this, handle));
}