
#include "loginframe.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/timemanager/timemanager.h"
#include "lib/include/timemanager/gametime.h"
#include "common/commonfunction.h"
#include "common/protocol/messageheader.h"
#include "common/protocol/msgcode.h"

class OuterCallBack : public MsgCallBack
{
public:
	OuterCallBack(NewFrame *frame) : m_frame(frame){}
	~OuterCallBack(){}

	void	Recv(GameMsg *msg)
	{
		m_frame->Recv(msg);
	}


private:
	NewFrame *m_frame;
};


class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(NewFrame *frame) : m_frame(frame){}
	~InnerCallBack(){}

	void	Recv(GameMsg *msg)
	{
		m_frame->Recv(msg);
	}


private:
	NewFrame *m_frame;
};

NewFrame::NewFrame()
{
	m_i_call_back = new InnerCallBack(this);
	m_o_call_back = new OuterCallBack(this);
}

NewFrame::~NewFrame()
{
	if (m_i_call_back)
	{
		delete m_i_call_back;
		m_i_call_back = NULL;
	}

	if (m_o_call_back)
	{
		delete m_o_call_back;
		m_o_call_back = NULL;
	}
	Exit();
}

bool NewFrame::InitConfig()
{
// 	m_login_server_handle = m_net_manager.InitServer(
// 		ServerConfig::Instance().m_ip[ServerConfig::LOGIN_SERVER],
// 		ServerConfig::Instance().m_server[ServerConfig::LOGIN_GATEWAY].port,
// 		ServerConfig::Instance().m_server[ServerConfig::LOGIN_GATEWAY].backlog,
// 		new Accepter(&m_net_manager, ServerConfig::Instance().m_ip[ServerConfig::GATEWAY_SERVER]));
// 
// 	if (m_login_server_handle == INVALID_NET_HANDLE)
// 	{
// 		return false;
// 	}

	m_database_server_handle = m_net_manager.ConnectServer(
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].ip,
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].port,
		new BaseListener(&m_net_manager),
		m_o_call_back);

	if (m_database_server_handle == INVALID_NET_HANDLE)
	{
		return false;
	}
	
	int a = 1;
	m_net_manager.Send(m_database_server_handle, (const char *)&a, sizeof(int));
	printf("fffffffffffffffffffffffffffffff\n");
//	m_rpc_server.Init(&m_net_manager, m_database_server_handle, 999);
	return Init();
}

bool NewFrame::Init()
{
	return true;
}


void NewFrame::Recv(GameMsg *msg)
{
	static int i = 1;
	int ret = *(int *)msg->data;
	
	if (i != ret)
	{
		exit(0);
	}

	if (ret % 100 == 0)
	{
		printf("ret = %d\n", ret);
	}
	if (i > 10000)
	{
		printf("success ret = %d\n", ret);
	}
	else
	{
		i++;
		m_net_manager.Send(m_database_server_handle, (const char *)&i, sizeof(int));
	}
	
	
	// 	if (!Function::ProtocolDecode(msg->data, msg->length))
	// 	{
	// 		return;
	// 	}

	// 	struct test
	// 	{
	// 		int a;
	// 		int b;
	// 	};
	// 
	// 	test *c = (test *)msg->data;
	// 	Send(msg->handle, (const char *)c, sizeof(test));
// 	EProtocol::MessageHeader *header = (EProtocol::MessageHeader *)msg->data;
// 	switch (header->msgid)
// 	{
// 	case EProtocol::MT_LOGIN_REQ_CS:
// 		OnLoginReq(msg->handle, msg->data, msg->length);
// 		break;
// 	case EProtocol::MT_LOGIN_CREATE_ROLE_CS:
// 		//		OnCreateRole(net_id, data, length);
// 		break;
// 	}
	delete msg;
}

void NewFrame::Update(unsigned int interval, time_t now)
{

}


void NewFrame::Exit()
{

}


void NewFrame::Wait()
{

}

void NewFrame::OnLoginReq(NetHandle handle, char *data, unsigned int length)
{
// 	if (length < sizeof(EProtocol::CSLogin))
// 	{
// 		return;
// 	}
// 
// 	EProtocol::CSLogin *cl = (EProtocol::CSLogin *)data;
// 
// 	cl->pname[sizeof(PlatName)-1] = '\0';
// 	if (std::string(cl->pname) == "")
// 	{
// 		return;
// 	}

	// 去数据库查找数据
	//Send(m_database_server_handle, data, length);
	//char buf[16];
	//RPCSerializer s(buf, 16);
	//m_rpc_server.Call(1, 2, s);
}
