
#include "netthread.h"
#include "callback.h"
#include "main/gateway.h"
#include "protocol/innerproto.h"
#include "lib/include/frame/baseaccepter.h"
#include "lib/include/frame/baselistener.h"
#include "lib/include/common/serverconfig.h"

NetThread::NetThread(ThreadManager *manager)
: BaseThread(manager)
, m_game_server(2)
{

}

void NetThread::Init(void *arg)
{
	int *index = (int *)arg;
	ServerInfo info1 = GatawayConfig::Instance().m_server[*index];
	m_net_manager.InitServer(info1.ip, info1.port, info1.backlog, new BaseAccepter(&m_net_manager), new CallBack(this));

	ServerInfo info2 = GatawayConfig::Instance().center;
	NetHandle handle = m_net_manager.ConnectServer(info2.ip, info2.port, new BaseListener(&m_net_manager), new InnerCallBack(this));
	if (handle != INVALID_NET_HANDLE)
	{
		m_net_manager.Listen();
		Inner::tocRegisterServer rs;
		rs.type = Inner::ST_GATE;
		rs.id = (unsigned short)*index;
		memcpy(rs.ip, info1.ip, sizeof(rs.ip));
		rs.port = info1.port;
		m_net_manager.Send(handle, (const char *)&rs, sizeof(Inner::tocRegisterServer));
	}
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
		NetHandle handle = m_net_manager.ConnectServer(br->ip, br->port, new BaseListener(&m_net_manager), new InnerCallBack(this));
		if (handle != INVALID_NET_HANDLE)
		{
			
		}
	}
}

bool NetThread::Run()
{

	return m_net_manager.Update();
}

void NetThread::RecvMsg(unsigned char sid, int len, const char *data)
{

}

