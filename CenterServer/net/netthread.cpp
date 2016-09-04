
#include "netthread.h"
#include "threadproto.h"
#include "main/center.h"
#include "src/messagehandler.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/socketthread.h"
#include "lib/include/inner/inneraccepter.h"
#include "lib/include/gate/gateaccepter.h"
#include "lib/include/base/function.h"

class CallBack : public MsgCallBack
{
public:
	CallBack(NetThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip){ m_thread->PushTimer(handle); };

	void	Recv(NetMsg *msg){ m_thread->Recv(msg); };

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

NetThread::NetThread(ThreadManager *manager)
: GateThread(manager)
, m_message_handler(this)
, m_id_pool(this)
, m_cur_thread_id(0)
{
	m_name = "net";
}

NetThread::~NetThread()
{
}

bool NetThread::Init()
{
	ServerInfo &info1 = CenterConfig::Instance().login;
	if (!InitServer(info1.ip, info1.port, info1.backlog, new GateAccepter(this, 1024), new CallBack(this)))
	{
		return false;
	}
	
	ServerInfo &info2 = CenterConfig::Instance().center;
	if (!InitServer(info2.ip, info2.port, info2.backlog, new InnerAccepter(this), new InnerCallBack(this)))
	{
		return false;
	}

	return true;
}

void NetThread::Ready()
{
	m_manager->SendMsg(GetThreadID(), ThreadProto::TP_LOAD_ROLE_MAX_ID, 0, NULL, m_id);
}

void NetThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{
	switch (type)
	{
	case ThreadProto::TP_LOAD_ROLE_MAX_ID_RET:
		m_id_pool.SetMaxID(*(unsigned int *)data);
		break;
	case ThreadProto::TP_LOAD_ROLE_RET:
	{
		ThreadProto::LoadRoleRet *lrr = (ThreadProto::LoadRoleRet *)data;
		printf("the ret name %s\n", lrr->name);
		break;	
	}
	case ThreadProto::TP_SAVE_ROLE_RET:

		// TODO 通知客户端是否创建角色成功

		//printf("create role success ...\n");
		break;
	default:
		break;
	}
}

void NetThread::InnerRecv(NetMsg *msg)
{
	static const int SHORT_LEN = sizeof(unsigned short);
	unsigned short router = (unsigned short)*msg->data;
	switch (router)
	{
	case PProto::TOC_REGISTER_SERVER:
		InsertServer(msg);
		
	default:
		break;
	}
}


void NetThread::InsertServer(NetMsg *msg)
{
	struct PProto::tocRegisterServer *rs = (struct PProto::tocRegisterServer *)msg->data;
	if (rs->type < PProto::ST_MAX)
	{
		Function::Info("new server register %d %s %d", rs->type, rs->ip, rs->port);
		OtherServer os;
		os.handle = msg->handle;
		os.id = rs->id;
		memcpy(os.ip, rs->ip, sizeof(os.ip));
		os.port = rs->port;
		m_server[rs->type].push_back(os);
		for (unsigned short i = 0; i < PProto::ST_MAX; ++i)
		{
			if (i != rs->type)
			{
				for (std::vector<OtherServer>::iterator itr = m_server[i].begin(); itr != m_server[i].end(); ++itr)
				{
					PProto::ctoBrocastRegister br;
					br.type = rs->type;
					br.id = rs->id;
					br.port = rs->port;
					memcpy(br.ip, rs->ip, sizeof(br.ip));
					Send(itr->handle, sizeof(PProto::ctoBrocastRegister), (const char *)&br);
				}
			}
		}
	}
}

void NetThread::RemoveServer(NetHandle handle)
{
	for (unsigned short i = 0; i < PProto::ST_MAX; ++i)
	{
		for (std::vector<OtherServer>::iterator itr = m_server[i].begin(); itr != m_server[i].end(); ++itr)
		{
			if (itr->handle == handle)
			{
				m_server[i].erase(itr);
				break;
			}
		}
	}
}

ThreadID NetThread::GetThreadID()
{
	if (m_cur_thread_id >= Center::MAX_DB_THREAD)
	{
		m_cur_thread_id = 0;
	}
	return Center::Instance().db_thread_id[m_cur_thread_id++];
}