
#include "testframe.h"
#include "lib/include/redis/redis.h"
#include "lib/include/frame/listener.h"

class RedisCallBack : public MsgCallBack
{
public:
	RedisCallBack(){}
	~RedisCallBack(){}

	void	Recv(GameMsg *msg)
	{
		printf("fuck\n");
	}
};

class RedisListener : public Listener
{
public:
	RedisListener(NetManager *manager, MsgCallBack *call_back)
		: Listener(manager)
	{
		m_call_back_handle = manager->RegisterCallBack(call_back);
	}
	~RedisListener(){}
	bool AnalyzeBuf()
	{
		const char *buf = m_recv_buf.GetBuf();
		GameMsg *msg = new GameMsg(m_handle, buf, m_recv_buf.Length());
		msg->call_back_handle = m_call_back_handle;
		m_net_manager->GetMsgQueue()->Push(msg);
		return true;
	};

private:
	int m_call_back_handle;
};

TestFrame::TestFrame()
: m_redis_call_back(new RedisCallBack)
{

}

TestFrame::~TestFrame()
{
	delete m_redis_call_back;
}


bool TestFrame::Init()
{
	Frame::Init();

	RedisListener *listener = new RedisListener(&m_net_manager, m_redis_call_back);
	Redis redis;
	redis.Connect("192.168.1.105", 6379, listener);
	// 	char *command = "set name jiaming\r\n";
	// 	redis.Command(command, strlen(command));

	char *command = "get name\r\n";
	redis.Command(command, strlen(command));
	return true;
}

void TestFrame::Update(unsigned int interval, time_t now)
{

}

void TestFrame::Exit()
{

}

void TestFrame::Wait()
{

}

void TestFrame::Recv(GameMsg *msg)
{

}

