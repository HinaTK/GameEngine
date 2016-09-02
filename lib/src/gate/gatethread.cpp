
#include "gatethread.h"
#include "gateaccepter.h"
#include "gatelistener.h"
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

	void	Recv(NetMsg *msg){ }

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

GateThread::GateThread(ThreadManager *manager, int index, ThreadID global)
: SocketThread(manager)
, m_index(index)
, m_role_msg(2048)
, m_global(global)
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
	if (itr != m_net_handler.End() && (*itr)->Type() == NetHandler::LISTENER)
	{
		
		((GateListener *)(*itr))->SetMsgID(index);
	}
	else{
		// todo 输出错误
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

void GateThread::PushCreator(NetHandle handle)
{
	m_creator.push(CreatorInfo{handle, time(NULL)}};
}

EXPORT GateThread * New::_GateThread(ThreadManager *manager, int index, ThreadID id)
{
	return new GateThread(manager, index, id);
}
