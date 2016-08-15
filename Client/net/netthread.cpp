
#include "netthread.h"
#include "protocol/innerproto.h"
#include "lib/include/gate/gatelistener.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/common/argsplit.h"
#include "lib/include/base/interface.h"
#include "CenterServer/net/src/proto.h"

NetThread::NetThread(ThreadManager *manager, SocketThread *st)
: BaseThread(manager, NULL, ThreadManager::EXIT_NORMAL)
, m_net_manager(manager)
{
	m_name = "net";
	m_net_manager.SetThread(st);
}

bool NetThread::Init()
{
	// todo 处理服务器断线
	m_server_handle = m_net_manager.SyncConnect("127.0.0.1", 12347, new GateListener(m_net_manager.GetThread()), new CallBack(this));
	if (m_server_handle == INVALID_NET_HANDLE)
	{
		return false;
	}
	return true;
}

void NetThread::InnerRecv(NetMsg *msg)
{
}


bool NetThread::Run()
{
	//Time::Sleep(1000);
	return m_net_manager.Update();
}

void NetThread::RecvData(short type, ThreadID sid, int len, const char *data)
{

}

bool NetThread::CMD(short type, ThreadID sid, int len, const char *data)
{
	char *buf = NULL;
	ArgSplit split((char *)data);
	split.GetArg(&buf);
	if (strncmp(data, "login", len) == 0)
	{
		Proto::csLogin login;
		memcpy(login.account, "aabbcc", sizeof("aabbcc"));
		login.sid = 123;

		m_net_manager.Send(m_server_handle, sizeof(Proto::csLogin), (const char *)&login);
	}
	else if (strcmp(data, "create") == 0)
	{
		if (split.GetArg(&buf))
		{
			Proto::csCreateRole role;
			memcpy(role.account, "ccddff", sizeof("ccddff"));
			int name_len = strlen(buf);
			name_len > GAME_NAME_SIZE - 1 ? name_len = GAME_NAME_SIZE - 1 : 0;
			memcpy(role.name, buf, name_len);
			role.name[name_len] = 0;
			role.sid = 1;

			m_net_manager.Send(m_server_handle, sizeof(Proto::csCreateRole), (const char *)&role);
		}
	}
	else if (strcmp(data, "createtest") == 0)
	{
		Proto::csCreateRole role;
		memcpy(role.account, "ccddff", sizeof("ccddff"));

		char buf2[8];
		for (int i = 1; i <= 1000; ++i)
		{
			itoa(i, buf2, 10);
			int name_len = strlen(buf2);
			name_len > GAME_NAME_SIZE - 1 ? name_len = GAME_NAME_SIZE - 1 : 0;
			memcpy(role.name, buf2, name_len);
			role.name[name_len] = 0;
			role.sid = i;
			m_net_manager.Send(m_server_handle, sizeof(Proto::csCreateRole), (const char *)&role);
		}
	}
	else return false;
	return true;
}

