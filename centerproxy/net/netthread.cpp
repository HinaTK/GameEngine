
#include "netthread.h"
#include "gateaccepter.h"
#include "gatelistener.h"
#include "other/serverconfig.h"
#include "other/proto.h"
#include "lib/include/common/argsplit.h"
#include "lib/include/base/interface.h"

class CallBack : public MsgCallBack
{
public:
	CallBack(NetThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip){};

    void	Recv(NetMsg *msg){m_thread->Recv(msg);}

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

	void	Connect(NetHandle handle, int flag){};

	void	Recv(NetMsg *msg){m_thread->InnerRecv(msg);}

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
	ServerInfo &info1 = ProxyConfig::Instance().server[m_index - 1];
	if (!InitServer(info1.ip, info1.port, info1.backlog, new GateAccepter(this), new CallBack(this)))
	{
		return false;
	}

	ServerInfo &info2 = CenterConfig::Instance().server;
	m_server_handle = SyncConnect(info2.ip, info2.port, new GateListener(this), new InnerCallBack(this));
	if (m_server_handle == INVALID_NET_HANDLE)
	{
		return false;
	}
	return true;
}

void NetThread::Recv(NetMsg *msg)
{
	// todo 在这里做一下监控，例如m_gate和m_proxy的大小
	// 接收到初始化后，分配一个唯一id，之后在场景分配对象id，
	// 并返回给本地网关，本地网关存储后，通知客户端切换场景
	// SCSceneEnter

	InnerProtocol::MessageHeader *header = (InnerProtocol::MessageHeader *)msg->data;
	if (header->msgid == InnerProtocol::MT_INNER_GATE_SERVER_USER_RECV ||
		header->msgid == InnerProtocol::MT_INNER_SCENE_TO_PROXY_TO_SCENE)
	{
		// 分配id todo 活动结束后，清空m_proxy，免得出错了，id溢出
		if (msg->handle >= m_gate.size())
		{
			m_gate.resize(msg->handle);
		}
		game::Hash<int, NetHandle> &hash = m_gate[msg->handle];
		game::Hash<int, NetHandle>::iterator itr = hash.Find(header->outer_netid);
		if (itr == hash.End())
		{
			unsigned short gate_net_id = header->outer_netid;
			header->outer_netid = m_proxy.Insert(Route{ msg->handle, header->outer_netid });
			hash.Push(gate_net_id, header->outer_netid);
		}
		else
		{
			header->outer_netid = itr->val;
		}	
	}

	Send(m_server_handle, msg->length, msg->data);
}

void NetThread::InnerRecv(NetMsg *msg)
{
	// 收到的数据，发送到网关
	InnerProtocol::MessageHeader *header = (InnerProtocol::MessageHeader*)msg->data;

	switch (header->msgid)
	{
	case InnerProtocol::MT_INNER_SERVER_GATE_USER_SEND_ONE:
	case InnerProtocol::MT_INNER_SERVER_GATE_USER_SEND_MUL:
	case InnerProtocol::MT_INNER_SERVER_GATE_USER_SEND_ALL:
		OnInnerRecv(msg->data, msg->length);
		break;
	case InnerProtocol::MT_INNER_SERVER_GATE_USER_DISCONNECT:
		OnInnerRecvDisconnect(msg->data, msg->length);
		break;
	default:
		break;
	}
}

void NetThread::OnInnerRecv(const char *data, int length)
{
	InnerProtocol::MessageHeader *header = (InnerProtocol::MessageHeader*)data;
	PROXY_TO_GATE::iterator itr = m_proxy.Find(header->outer_netid);
	if (itr != m_proxy.End())
	{
		header->outer_netid = itr->gate_net_id;
		Send(itr->handle, length, data);
	}
}

// todo 在中心服务器中加判断,调用下线时，判断是否需要重新保存数据
void NetThread::OnInnerRecvDisconnect(const char *data, int length)
{
	InnerProtocol::MessageHeader *header = (InnerProtocol::MessageHeader*)data;
	PROXY_TO_GATE::iterator itr = m_proxy.Find(header->outer_netid);
	if (itr != m_proxy.End())
	{
		// todo 在网关中修改路由
		Send(itr->handle, length, data);
	}
}

void NetThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{

}

bool NetThread::CMD(TPT type, ThreadID sid, int len, const char *data)
{
	char *buf;
	ArgSplit split((char *)data);
	split.GetArg(&buf);
	if (strcmp(buf, "test") == 0)
	{
		if (split.GetLeft(&buf))
		{
			int id = atoi(buf);
			m_db_manager.Test(id);
			return true;
		}
	}
	else if (strcmp(buf, "test2") == 0)
	{
		if (split.GetLeft(&buf))
		{
			int id = atoi(buf);
			m_db_manager.SaveRoleMaxID(id);
			return true;
		}
	}
	return false;
}

