#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include "frame/frame.h"
#include "common/commonvariable.h"
#include "common/datastructure/msgqueue.h"
#include "libcommon/thread.h"
#include "message/messagefunction/messagehandler.h"

class LoginFrame : public Frame
{
public:
	static const UInt32 UpdateSleepTime = 80;		// 单位毫秒，每隔80毫秒更新一次
	static const UInt32 SendSleepTime = 50;			// 单位毫秒，当发送消息队列为空时，睡眠50毫秒
	static const UInt32 RecvSleepTime = 50;			// 单位毫秒，当接收消息队列为空和没有到更新时间，睡眠50毫秒

    ~LoginFrame();

    static LoginFrame &Instance()
    {
        static LoginFrame frame;
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
    void Update();  //更新

	void	Exit();
	void	Wait();
	void	Recv(GameMsg *msg);

	void OnRecv(NetID user_id, char *msg, UInt16 length);

	void OnSend(NetID user_id, char *msg, UInt16 length);

	MsgQueue	*GetSendQueue(){ return &m_send_queue; }

	MsgQueue	*GetRecvQueue(){ return &m_recv_queue; }

public:
	Thread	m_recv_client_thread;
	Thread	m_recv_server_thread;
	Thread	m_send_thread;
    NetID	m_database_server_net_id;
	NetID	m_gateway_server_net_id;

private:
	LoginFrame();

	//TimeEventManager m_time_event_manager;
	MessageHandler		m_message_handler;
	
	MsgQueue			m_send_queue;
	MsgQueue			m_recv_queue;
};

#endif