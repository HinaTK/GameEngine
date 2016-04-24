
#include "netthread.h"
#include "callback.h"
#include "lib/include/frame/baseaccepter.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/socketthread.h"
#include "protocol/innerproto.h"
#include "router.h"

NetThread::NetThread(ThreadManager *manager)
: BaseThread(manager, NULL, ThreadManager::EXIT_NORMAL)
, m_net_manager(new NetManager)
{

}

NetThread::~NetThread()
{
	delete m_net_manager;
}

void NetThread::Init(void *arg)
{
	SocketThread *st = new SocketThread(m_manager, m_net_manager);
	m_net_manager->SetThread(st);

	ServerInfo info1 = CenterConfig::Instance().login;
	m_net_manager->InitServer(info1.ip, info1.port, info1.backlog, new BaseAccepter(m_net_manager), new CallBack(this));

	ServerInfo info2 = CenterConfig::Instance().center;
	m_net_manager->InitServer(info2.ip, info2.port, info2.backlog, new BaseAccepter(m_net_manager), new InnerCallBack(this));
}


bool NetThread::Run()
{
	return m_net_manager->Update();
}

void NetThread::RecvData(short type, int sid, int len, const char *data)
{

}

void NetThread::InnerRecv(GameMsg *msg)
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


void NetThread::InsertServer(GameMsg *msg)
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
					m_net_manager->Send(itr->handle, sizeof(Inner::ctoBrocastRegister), (const char *)&br);
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

