
#ifndef GAME_FRAME_H
#define GAME_FRAME_H

#include "define.h"
#include "common/datastructure/gamehash.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/timemanager/timemanager.h"
#include "thread/threadmanager.h"
#include "callback.h"

class NewFrame : public Frame
{
public:
    
	static const UInt32 UPDATE_INTERNAL = 80;		// 单位毫秒，每隔80毫秒更新一次
	static const UInt32 SendSleepTime = 50;			// 单位毫秒，当发送消息队列为空时，睡眠50毫秒
	static const UInt32 RecvSleepTime = 50;			// 单位毫秒，当接收消息队列为空和没有到更新时间，睡眠50毫秒

    ~NewFrame();

    static NewFrame &Instance()
    {
        static NewFrame frame;
        return frame;
    }

	bool	InitConfig();

    bool	Init();    //初始化

	void	Update(unsigned int interval, time_t now);  //更新
    void	Exit();
	void	Wait();
	void	OuterRecv(GameMsg *msg);
	void	InnerRecv(GameMsg *msg);

	void	PushMsg(GameMsg *msg, SceneID scene_id = 0);

	void	ChangeServer();

public:

	NetHandle	m_database_server_handle;
	SOCKET		m_gateway_server_net_id;
private:
	NewFrame();

    OuterCallBack		m_o_call_back;
    InnerCallBack		m_i_call_back;

	TimeEventManager	m_time_event_manager;
	ThreadManager		m_thread_manager;

	typedef game::Hash<NetHandle, int> NET_HANDLE_THREAD_HASH;
	NET_HANDLE_THREAD_HASH m_net_handle_thread_hash;
	
};

#endif // FRAME_H
