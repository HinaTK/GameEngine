
#include "testframe.h"
#include "lib/include/redis/redis.h"
#include "lib/include/redis/redisprotocol.h"

class RedisCallBack : public MsgCallBack
{
public:
	RedisCallBack(){}
	~RedisCallBack(){}

	void	Recv(GameMsg *msg)
	{
		printf("msg = %s\n", msg->data);
	}
};

TestFrame::TestFrame()
: m_redis_call_back(NULL)
{

}

TestFrame::~TestFrame()
{
	delete m_redis_call_back;
}


bool TestFrame::Init()
{
	Frame::Init();

// 	RedisListener *listener = new RedisListener(&m_net_manager, m_redis_call_back);
// 	Redis redis;
// 	redis.Connect("192.168.1.105", 6379, listener);
	//char *command = "seet name4 jiaming\r\n";

	//char *command = "get name22222\r\n";

	//char *command = "mset name1 jiaming1 name2 jiaming2\r\n";

	//char *command = "mget name22 age22\r\n";

	//char *command = "incr age\r\n";
	//char *command = "blpop jjjj 1\r\n";
	//char *command = "eval \"return redis.call('set', 'ggg', 'bar')\" 0\r\n";
	//char *command = "get name1\r\nget name2\r\n";
// 	char *command = "get name1\r\nget name2\r\n";
// 	redis.Command(command, strlen(command));
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



