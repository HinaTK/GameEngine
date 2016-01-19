
#include "gameframe.h"
#include "common/datastructure/msgqueue.h"
#include "common/protocol/messageheader.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/tinyxml/tinyxml.h"
#include "lib/include/timemanager/gametime.h"
#include "poolconfig/test.h"


NewFrame::NewFrame()
: m_o_call_back(this)
, m_i_call_back(this)
{

}

NewFrame::~NewFrame()
{

}

static const int test_num = 100000;
std::thread *test_thread = NULL;
static unsigned long long begin = GameTime::Instance().MilliSecond();
void *ttt(void * arg)
{
    NewFrame *frame = (NewFrame *)arg;
    NetManager *net_manager = frame->GetNetManager();
    for (int i = 1; i <= test_num; ++i)
    {
        net_manager->Send(frame->m_database_server_handle, (const char *)&i, sizeof(int));
    }
    return NULL;
}

bool NewFrame::InitConfig()
{
// 	if (!m_net_manager.InitServer(
// 		ServerConfig::Instance().m_server[ServerConfig::GAME_SERVER].ip,
// 		ServerConfig::Instance().m_server[ServerConfig::GAME_SERVER].port,
// 		ServerConfig::Instance().m_server[ServerConfig::GAME_SERVER].backlog,
// 		new Accepter(&m_net_manager), 
//         &m_o_call_back))
// 	{
// 		return false;
// 	}
// 
//     m_database_server_handle = m_net_manager.ConnectServer(
//         ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].ip,
//         ServerConfig::Instance().m_server[ServerConfig::DATABASE_SERVER].port,
//         new BaseListener(&m_net_manager),
//         &m_i_call_back);
// 
//     if (m_database_server_handle == INVALID_NET_HANDLE)
//     {
//         printf("connect data server fail ...\n");
//         return false;
//     }

	// 读取配置,设置m_game_thread_num的值
// 	m_game_thread = new GameThread*[m_game_thread_num];
// 	for (int i = 0; i < m_game_thread_num; ++i)
// 	{
// 		m_game_thread[i] = new GameThread(i + 1);
// 	}
	
//    for (int i = 1; i <= 1; ++i)
//    {
//        m_net_manager.Send(m_database_server_handle, (const char *)&i, sizeof(int));
//    }

//      test_thread = new std::thread(::ttt, this);
//      begin = GameTime::Instance().MilliSecond();
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
	m_thread_manager.Start();
	return true;
}

int i = 1;
// 构架更新
void NewFrame::Update(unsigned int interval, time_t now)
{
	//m_time_event_manager.Update(now);
	//StmtSelect();
	//StmtInsert();
	//StmtUpdate();
	//StmtDelete();
	//exit(0);
	ThreadMsg *msg = new ThreadMsg(4, (const char *)&i);
	m_thread_manager.PushMsg(ThreadManager::T_DB, msg);
	i++;
	if (i > 20)
	{
		SetExit();
	}
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

	int ret = *(int *)msg->data;

    if (ret >= test_num || ret <= 0)
	{
        printf("fuck exit ret = %d %d\n", ret, GameTime::Instance().MilliSecond() - begin);
		SetExit();
	}
	else
	{
//        printf("ret = %d\n", ret);
//		int begin = ret * 10 + 1;
//		for (int i = begin; i < begin + 10; ++i)
//		{
//			m_net_manager.Send(m_database_server_handle, (const char *)&i, sizeof(int));
//		}

	}

    if (ret % 1000 == 0)
	{
		printf("ret = %d\n", ret);
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
	m_thread_manager.Exit();
	printf("game server exit\n");
}

void NewFrame::Wait()
{
	m_thread_manager.Wait();
//	for (int i = 0; i < m_game_thread_num; ++i)
//	{
//		m_game_thread[i]->Wait();
//	}
}



