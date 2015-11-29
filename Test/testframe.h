
#ifndef TEST_FRAME_H
#define TEST_FRAME_H

#include "lib/include/frame/frame.h"

class RedisCallBack;
class TestFrame : public Frame
{
public:

	virtual ~TestFrame();

	static TestFrame &Instance()
	{
		static TestFrame frame;
		return frame;
	}

	bool	Init();    //初始化


	void	Update(unsigned int interval, time_t now);  //更新

	void	Exit();

	void	Wait();

	void	Recv(GameMsg *msg);

public:
	void	Test1();

private:
	TestFrame();

	RedisCallBack	*m_redis_call_back;
};

#endif