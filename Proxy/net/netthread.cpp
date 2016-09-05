
#include "netthread.h"
#include "lib/include/gate/gatelistener.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/common/argsplit.h"
#include "lib/include/base/interface.h"
#include "CenterServer/net/src/proto.h"

class CallBack : public MsgCallBack
{
public:
	CallBack(NetThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip){};

    void	Recv(NetMsg *msg){};

	void	Disconnect(NetHandle handle, int err, int reason){};

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

	void	Recv(NetMsg &msg){};

	void	Disconnect(NetHandle handle, int reason){};

private:
	NetThread *m_thread;
};


NetThread::NetThread(ThreadManager *manager)
: SocketThread(manager)
{
	m_name = "net";
}

bool NetThread::Init()
{
	ServerInfo &info1 = ProxyConfig::Instance().proxy;
	if (!InitServer(info1.ip, info1.port, info1.backlog, new InnerListener(this), new InnerCallBack(this)))
	{
		return false;
	}
	
	ServerInfo &info2 = GameConfig::Instance().center;
	m_cneter_handle = SyncConnect(info2.ip, info2.port, new InnerListener(this), new InnerCallBack(this));

	if (m_cneter_handle != INVALID_NET_HANDLE)
	{
		PProto::tocRegisterServer rs;
		rs.type = PProto::ST_PROXY;
		rs.id = 1;
		memcpy(rs.ip, info1.ip, sizeof(rs.ip));
		rs.port = info1.port;
		Send(m_cneter_handle, sizeof(PProto::tocRegisterServer), (const char *)&rs);
	}
	else return false;

	return true;
}

void NetThread::InnerRecv(NetMsg *msg)
{
}

void NetThread::RecvData(TPT type, ThreadID sid, int len, const char *data)
{

}

bool NetThread::CMD(TPT type, ThreadID sid, int len, const char *data)
{
	char *buf = NULL;
	ArgSplit split((char *)data);
	split.GetArg(&buf);
	if (strncmp(data, "login", len) == 0)
	{
		Proto::csLogin login;
		memcpy(login.account, "aabbcc", sizeof("aabbcc"));
		login.sid = 123;

		Send(m_server_handle, sizeof(Proto::csLogin), (const char *)&login);
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

			Send(m_server_handle, sizeof(Proto::csCreateRole), (const char *)&role);
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
			Send(m_server_handle, sizeof(Proto::csCreateRole), (const char *)&role);
		}
	}
	else return false;
	return true;
}

