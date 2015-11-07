
#include "loginframe.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/timemanager/timemanager.h"
#include "common/commonfunction.h"
#include "common/protocol/messageheader.h"
#include "common/protocol/msgcode.h"

class OuterCallBack : public MsgCallBack
{
public:
	OuterCallBack(LoginFrame *frame) : m_frame(frame){}
	~OuterCallBack(){}

	void	Recv(GameMsg *msg)
	{
		m_frame->Recv(msg);
	}


private:
	LoginFrame *m_frame;
};


class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(LoginFrame *frame) : m_frame(frame){}
	~InnerCallBack(){}

	void	Recv(GameMsg *msg)
	{
		m_frame->Recv(msg);
	}


private:
	LoginFrame *m_frame;
};

LoginFrame::LoginFrame()
{
	m_i_call_back = new InnerCallBack(this);
	m_o_call_back = new OuterCallBack(this);
}

LoginFrame::~LoginFrame()
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

bool LoginFrame::InitConfig()
{
	if (!m_net_manager.InitServer(
		ServerConfig::Instance().m_ip[ServerConfig::LOGIN_SERVER],
		ServerConfig::Instance().m_server[ServerConfig::LOGIN_GATEWAY].port,
		ServerConfig::Instance().m_server[ServerConfig::LOGIN_GATEWAY].backlog,
		m_login_server_net_id,
		new Accepter(&m_net_manager, ServerConfig::Instance().m_ip[ServerConfig::LOGIN_SERVER], m_i_call_back)))
	{
		return false;
	}

	m_database_server_handle = m_net_manager.ConnectServer(
		ServerConfig::Instance().m_ip[ServerConfig::DATABASE_SERVER],
		ServerConfig::Instance().m_server[ServerConfig::DATABASE_LOGIN].port,
		new BaseListener(&m_net_manager, m_o_call_back));

	if (m_database_server_handle == INVALID_NET_HANDLE)
	{
		return false;
	}
	
	int a = 123;
	m_net_manager.Send(m_database_server_handle, (const char *)&a, 4);
//	m_rpc_server.Init(&m_net_manager, m_database_server_handle, 999);
	return Init();
}

bool LoginFrame::Init()
{
	return true;
}


void LoginFrame::Recv(GameMsg *msg)
{
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
	EProtocol::MessageHeader *header = (EProtocol::MessageHeader *)msg->data;
	switch (header->msgid)
	{
	case EProtocol::MT_LOGIN_REQ_CS:
		OnLoginReq(msg->handle, msg->data, msg->length);
		break;
	case EProtocol::MT_LOGIN_CREATE_ROLE_CS:
		//		OnCreateRole(net_id, data, length);
		break;
	}
	delete msg;
}

void LoginFrame::Update(unsigned int interval, time_t now)
{

}


void LoginFrame::Exit()
{

}


void LoginFrame::Wait()
{

}

void LoginFrame::OnLoginReq(NetHandle handle, char *data, unsigned int length)
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
