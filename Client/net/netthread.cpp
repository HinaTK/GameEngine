
#include "netthread.h"
#include "lib/include/inner/innerlistener.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/common/argsplit.h"
#include "lib/include/base/interface.h"
#include "lib/include/base/function.h"
#include "CenterServer/net/src/proto.h"

class CallBack : public MsgCallBack
{
public:
	CallBack(NetThread *t)
		: MsgCallBack()
		, m_thread(t){}
	~CallBack(){}

	void	Accept(NetHandle handle, const char *ip)
	{
		m_thread->RemoveHandler(m_thread->GetServerHandle());
		m_thread->SetServerHandle(handle);
	};

	void	Recv(NetMsg *msg){ m_thread->InnerRecv(msg); };

	void	Disconnect(NetHandle handle, int err, int reason)
	{
		Function::Error("disconnect %d %d %d", handle, err, reason);
	};

private:
	NetThread *m_thread;
};

NetThread::NetThread(ThreadManager *manager)
: SocketThread(manager)
, m_server_handle(INVALID_NET_HANDLE)
{
	m_name = "net";
}

bool NetThread::Init()
{
	m_server_handle = SyncConnect("127.0.0.1", 12347, new InnerListener(this), new CallBack(this));

	if (m_server_handle == INVALID_NET_HANDLE)
	{
		return false;
	}
	char *HANDSHAKE = "JIAMING";
	Send(m_server_handle, strlen(HANDSHAKE), HANDSHAKE);
	return true;
}

void NetThread::InnerRecv(NetMsg *msg)
{
	if (msg->length < 2)
	{
		Function::Error("is not a right protocol");
		return;
	}
	unsigned short * type = (unsigned short *)msg->data;
	switch(*type)
	{
	case Proto::SC_LOGIN:
	{
		Proto::scLogin *l = (Proto::scLogin *)msg->data;
		AsyncConnect(l->ip, l->port, new InnerListener(this), new CallBack(this));
		break;
	}
	case Proto::SC_LOGIN_ERR:
	{
		Proto::scLoginErr *le = (Proto::scLoginErr *)msg->data;
	}
	}
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

