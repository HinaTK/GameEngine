#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include "common/commonvariable.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/timemanager/timemanager.h"


class GameFrame : public Frame
{
public:
    
	static const UInt32 UPDATE_INTERNAL = 80;		// 单位毫秒，每隔80毫秒更新一次
	static const UInt32 SendSleepTime = 50;			// 单位毫秒，当发送消息队列为空时，睡眠50毫秒
	static const UInt32 RecvSleepTime = 50;			// 单位毫秒，当接收消息队列为空和没有到更新时间，睡眠50毫秒

    ~GameFrame();

    static GameFrame &Instance()
    {
        static GameFrame frame;
        return frame;
    }

	bool	InitConfig();

    bool	Init();    //初始化

    void	Update(time_t now);  //更新

    void	Exit();
	void	Wait();
	void	Recv(GameMsg *msg);

public:

	NetID		m_database_server_net_id;
	NetID		m_gateway_server_net_id;
private:
	GameFrame();

	TimeEventManager	m_time_event_manager;
	
};

#endif // FRAME_H
