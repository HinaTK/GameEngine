#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include "common/commonvariable.h"
#include "common/datastructure/msgqueue.h"
#include "libcommon/thread.h"
#include "frame/frame.h"
#include "libtimemanager.h"


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

    /*
     *Init 主要是加载配置，及将dll加载到框架当中
     */
    bool Init();    //初始化

    /*
     *Update 主要是更新一些状态，例如当客户端发送过来的一些数据，进程间通信的一些数据；可设定一定的时间间隔来进行update
     */
    void Update(time_t now);  //更新

    /*
     *Run 当状态更新后，将对游戏逻辑进行处理
     */
    //bool Run();     //运行

    /*
     *对游戏进行析构
     */
    void Exit();

	void InteanalRecv(NetID user_id, char *msg, UInt16 length);

	//void OnSend(NetID user_id, char *msg, UInt16 length);

	MsgQueue	*GetSendQueue(){ return &m_send_queue; }

	MsgQueue	*GetRecvQueue(){ return &m_recv_queue; }
public:
	Thread		m_recv_client_thread;
	Thread		m_recv_server_thread;
	Thread		m_send_thread;
//	Thread		m_internal_recv_thread;
	NetID		m_database_server_net_id;
	NetID		m_gateway_server_net_id;
private:
	GameFrame();

	TimeEventManager	m_time_event_manager;
	MsgQueue			m_send_queue;
	MsgQueue			m_recv_queue;
	
};

#endif // FRAME_H
