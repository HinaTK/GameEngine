
#include "netthread.h"
#include "main/gateway.h"
#include "common/proto.h"
#include "lib/include/gate/gateaccepter.h"
#include "lib/include/gate/gatelistener.h"
#include "lib/include/common/serverconfig.h"

NetThread::NetThread(ThreadManager *manager, int index)
: SocketThread(manager)
, m_index(index)
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
	ServerInfo info = GatawayConfig::Instance().m_server[m_index];
	if (!InitServer(info.ip, info.port, info.backlog, new GateAccepter(this, 1024), new CallBack(this)))
	{
		return false;
	}

	ServerInfo info2 = GatawayConfig::Instance().center;
	NetHandle handle = SyncConnect(info2.ip, info2.port, new GateListener(this), m_inner_callback);
	if (handle == INVALID_NET_HANDLE)
	{
		return false;
	}
	PProto::tocRegisterServer rs;
	rs.type = PProto::ST_GATE;
	rs.id = (unsigned short)m_index;
	memcpy(rs.ip, info.ip, sizeof(rs.ip));
	rs.port = info.port;
	Send(handle, sizeof(PProto::tocRegisterServer), (const char *)&rs);
	return true;
}

void NetThread::InnerRecv(NetMsg *msg)
{
	static const int SHORT_LEN = sizeof(unsigned short);
	unsigned short router = (unsigned short)*msg->data;
	switch (router)
	{
	case PProto::CTO_BROCAST_REGISTER:
		InsertGame(msg);
	default:
		break;
	}
}


void NetThread::InsertGame(NetMsg *msg)
{
	PProto::ctoBrocastRegister *br = (PProto::ctoBrocastRegister *)msg->data;
	if (br->type == PProto::ST_GAME)
	{
		for (game::Vector<GameServer>::iterator itr = m_game_server.Begin(); itr != m_game_server.End(); ++itr)
		{
			if (itr->id == br->id && itr->type == itr->type)
			{
				m_game_server.Erase(itr);
			}
		}
		AsyncConnect(br->ip, br->port, new GateListener(this), m_inner_callback, br->id);
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

void NetThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{

}

