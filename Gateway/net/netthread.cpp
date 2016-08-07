
#include "netthread.h"
#include "main/gateway.h"
#include "protocol/innerproto.h"
#include "lib/include/gate/gateaccepter.h"
#include "lib/include/gate/gatelistener.h"
#include "lib/include/common/serverconfig.h"

NetThread::NetThread(ThreadManager *manager, void *arg)
: BaseThread(manager, arg, ThreadManager::EXIT_NORMAL)
, m_net_manager(manager)
, m_inner_callback(new InnerCallBack(this))
, m_game_server(2)
{
	m_name = "net";
}

NetThread::~NetThread()
{
	if (m_inner_callback != NULL)
	{
		delete m_inner_callback;
		m_inner_callback = NULL;
	}
}

bool NetThread::Init()
{
	SocketThread *st = new SocketThread(m_manager, &m_net_manager);
	m_net_manager.SetThread(st);

	int *index = (int *)m_arg;
	ServerInfo info = GatawayConfig::Instance().m_server[*index];
	m_net_manager.InitServer(info.ip, info.port, info.backlog, new GateAccepter(m_net_manager.GetThread(), 1024), new CallBack(this));

	ServerInfo info2 = GatawayConfig::Instance().center;
	NetHandle handle = m_net_manager.SyncConnect(info2.ip, info2.port, new GateListener(m_net_manager.GetThread()), m_inner_callback);
	if (handle != INVALID_NET_HANDLE)
	{
		Inner::tocRegisterServer rs;
		rs.type = Inner::ST_GATE;
		rs.id = (unsigned short)*index;
		memcpy(rs.ip, info.ip, sizeof(rs.ip));
		rs.port = info.port;
		m_net_manager.Send(handle, sizeof(Inner::tocRegisterServer), (const char *)&rs);
	}
	delete m_arg;
	m_arg = NULL;
	return true;
}

void NetThread::InnerRecv(GameMsg *msg)
{
	static const int SHORT_LEN = sizeof(unsigned short);
	unsigned short router = (unsigned short)*msg->data;
	switch (router)
	{
	case Inner::CTO_BROCAST_REGISTER:
		InsertGame(msg);
	default:
		break;
	}
}


void NetThread::InsertGame(GameMsg *msg)
{
	Inner::ctoBrocastRegister *br = (Inner::ctoBrocastRegister *)msg->data;
	if (br->type == Inner::ST_GAME)
	{
		for (game::Vector<GameServer>::iterator itr = m_game_server.Begin(); itr != m_game_server.End(); ++itr)
		{
			if (itr->id == br->id && itr->type == itr->type)
			{
				m_game_server.Erase(itr);
			}
		}
		m_net_manager.AsyncConnect(br->ip, br->port, new GateListener(m_net_manager.GetThread()), m_inner_callback, br->id);
	}
}

void NetThread::ConnetRet(NetHandle handle, int flag)
{
	for (game::Vector<GameServer>::iterator itr = m_game_server.Begin(); itr != m_game_server.End(); ++itr)
	{
		if (itr->id == (unsigned short)flag)
		{
			itr->handle = handle;
			break;
		}
	}
}

bool NetThread::Run()
{

	return m_net_manager.Update();
}

void NetThread::RecvData(short type, ThreadID sid, int len, const char *data)
{

}

