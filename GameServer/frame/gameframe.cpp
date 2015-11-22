
#include "gameframe.h"
#include "common/datastructure/msgqueue.h"
#include "common/protocol/messageheader.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/tinyxml/tinyxml.h"
#include "poolconfig/test.h"

class OuterCallBack : public MsgCallBack
{
public:
	OuterCallBack(NewFrame *frame) : m_frame(frame){}
	~OuterCallBack(){}

	void	Recv(GameMsg *msg){m_frame->OuterRecv(msg);}
private:
	NewFrame *m_frame;
};

class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(NewFrame *frame) : m_frame(frame){}
	~InnerCallBack(){}

	void	Recv(GameMsg *msg){m_frame->InnerRecv(msg);}
private:
	NewFrame *m_frame;
};


NewFrame::NewFrame()
: m_game_thread_num(10)
, m_game_thread(NULL)
{
	m_o_call_back = new OuterCallBack(this);
	m_i_call_back = new InnerCallBack(this);
}

NewFrame::~NewFrame()
{
	if (m_game_thread != NULL)
	{
		for (int i = 0; i < m_game_thread_num; ++i)
		{
			delete m_game_thread[i];
		}
		delete m_game_thread;
		m_game_thread = NULL;
	}

	if (m_o_call_back)
	{
		delete m_o_call_back;
		m_o_call_back = NULL;
	}

	if (m_i_call_back)
	{
		delete m_i_call_back;
		m_i_call_back = NULL;
	}
	Exit();

}

bool NewFrame::InitConfig()
{
	if (!m_net_manager.InitServer(
		ServerConfig::Instance().m_server[ServerConfig::GAME_SERVER].ip,
		ServerConfig::Instance().m_server[ServerConfig::GAME_SERVER].port,
		ServerConfig::Instance().m_server[ServerConfig::GAME_SERVER].backlog,
		new Accepter(&m_net_manager), 
		m_o_call_back))
	{
		return false;
	}

    m_database_server_handle = m_net_manager.ConnectServer(
        ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].ip,
        ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].port,
        new BaseListener(&m_net_manager),
        m_i_call_back);

    if (m_database_server_handle == INVALID_NET_HANDLE)
    {
        return false;
    }

	// 读取配置,设置m_game_thread_num的值
// 	m_game_thread = new GameThread*[m_game_thread_num];
// 	for (int i = 0; i < m_game_thread_num; ++i)
// 	{
// 		m_game_thread[i] = new GameThread(i + 1);
// 	}
	
    int a = 1;
    m_net_manager.Send(m_database_server_handle, (const char *)&a, sizeof(int));
// 	struct Test
// 	{
// 		Test() :header(0){}
// 		IProtocol::MessageHeader	header;
// 		char a;
// 		short b;
// 		int c;
// 	};
// 	Test test;
// 	test.a = 1;
// 	test.b = 2;
// 	test.c = 3;
// 	test.header.msg_len = (sizeof(Test));
// 	m_net_manager.Send(m_database_server_net_id, (const char *)&test, test.header.msg_len);
// // 	send(m_database_server_net_id, (const char *)&test, 1288, 0);
	return this->Init();
}

// 框架初始化
bool NewFrame::Init()
{
	// 读取场景配置,根据不同的配置将不同的场景分配到不同的工作线程
	return true;
}

bool NewFrame::Run()
{
// 	for (int i = 0; i < m_game_thread_num; ++i)
// 	{
// 		m_game_thread[i]->Run();
// 	}

	return Frame::Run();
}

// 构架更新
void NewFrame::Update(unsigned int interval, time_t now)
{
	//m_time_event_manager.Update(now);
	//StmtSelect();
	//StmtInsert();
	//StmtUpdate();
	//StmtDelete();
	//exit(0);
}

void NewFrame::OuterRecv(GameMsg *msg)
{
	NET_HANDLE_THREAD_HASH::iterator itr = m_net_handle_thread_hash.Find(msg->handle);
	if (itr != m_net_handle_thread_hash.End())
	{

	}
	else
	{
		delete msg;
	}
}


void NewFrame::InnerRecv(GameMsg *msg)
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
}

/* 
	工作线程相互通信
	scene_id 等于0，表示消息放到全局线程处理
*/
void NewFrame::PushMsg(GameMsg *msg, SceneID scene_id /*= 0*/)
{
	if (scene_id == 0)
	{
	}
}


void NewFrame::Exit()
{
	// 进程退出，线程也随之退出

	printf("game server exit\n");
}

void NewFrame::Wait()
{
//	for (int i = 0; i < m_game_thread_num; ++i)
//	{
//		m_game_thread[i]->Wait();
//	}
}



