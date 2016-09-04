
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
, m_timer_queue(New::_TimerQueue(4))
{
	m_name = "gate";
}

GateThread::~GateThread()
{
	delete m_timer_queue;
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

void GateThread::PushTimer(NetHandle handle)
{
	m_timer_queue->AddEvent(new HandshakeTimeEvent(this, handle));
}