
#include "netthread.h"
#include "callback.h"
#include "threadproto.h"
#include "main/center.h"
#include "src/messagehandler.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/socketthread.h"
#include "lib/include/inner/inneraccepter.h"
#include "lib/include/gate/gateaccepter.h"


NetThread::NetThread(ThreadManager *manager, SocketThread *st)
: BaseThread(manager, ThreadManager::EXIT_NORMAL)
, m_net_manager(manager)
, m_message_handler(this)
, m_id_pool(this)
, m_cur_thread_id(0)
{
	m_name = "net";
	m_net_manager.SetThread(st);
}

NetThread::~NetThread()
{
}

bool NetThread::Init()
{
	ServerInfo &info1 = CenterConfig::Instance().login;
	if (!m_net_manager.InitServer(info1.ip, info1.port, info1.backlog, new GateAccepter(m_net_manager.GetThread(), 1024), new CallBack(this)))
	{
		return false;
	}
	
	ServerInfo &info2 = CenterConfig::Instance().center;
	if (!m_net_manager.InitServer(info2.ip, info2.port, info2.backlog, new InnerAccepter(m_net_manager.GetThread()), new InnerCallBack(this)))
	{
		return false;
	}

	return true;
}

bool NetThread::Ready()
{
	m_manager->SendMsg(GetThreadID(), ThreadProto::TP_LOAD_ROLE_MAX_ID, 0, NULL, m_id);
	return true;
}

bool NetThread::Run()
{
    return m_net_manager.Update();
}

void NetThread::RecvData(short type, ThreadID sid, int len, const char *data)
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
	case Inner::TOC_REGISTER_SERVER:
		InsertServer(msg);
		
	default:
		break;
	}
}


void NetThread::InsertServer(NetMsg *msg)
{
	struct Inner::tocRegisterServer *rs = (struct Inner::tocRegisterServer *)msg->data;
	if (rs->type < Inner::ST_MAX)
	{
		OtherServer os;
		os.handle = msg->handle;
		os.id = rs->id;
		memcpy(os.ip, rs->ip, sizeof(os.ip));
		os.port = rs->port;
		m_server[rs->type].push_back(os);
		for (unsigned short i = 0; i < Inner::ST_MAX; ++i)
		{
			if (i != rs->type)
			{
				for (std::vector<OtherServer>::iterator itr = m_server[i].begin(); itr != m_server[i].end(); ++itr)
				{
					Inner::ctoBrocastRegister br;
					br.type = rs->type;
					br.id = rs->id;
					br.port = rs->port;
					memcpy(br.ip, rs->ip, sizeof(br.ip));
					m_net_manager.Send(itr->handle, sizeof(Inner::ctoBrocastRegister), (const char *)&br);
				}
			}
		}
	}
}

void NetThread::RemoveServer(NetHandle handle)
{
	for (unsigned short i = 0; i < Inner::ST_MAX; ++i)
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