#ifndef DATABASEFRAME_H
#define DATABASEFRAME_H

#include "libtimemanager.h"
#include "frame/frame.h"
#include "../msghandler/messagehandler.h"

class DatabaseFrame : public Frame
{
public:

    ~DatabaseFrame();

    static DatabaseFrame &Instance()
    {
        static DatabaseFrame frame;
        return frame;
    }

	bool InitConfig();
    /*
     *Init 主要是加载配置，及将dll加载到框架当中
     */
    bool	Init();    //初始化

    /*
     *Update 主要是更新一些状态，例如当客户端发送过来的一些数据，进程间通信的一些数据；可设定一定的时间间隔来进行update
     */
    void	Update(time_t now);  //更新

    /*
     *Run 当状态更新后，将对游戏逻辑进行处理
     */
    //bool Run();     //运行

    /*
     *对游戏进行析构
     */
    void	Exit();

	void	OnRecv(NetID user_id, char *msg, unsigned int length);

	//void	OnSend(NetID user_id, char *msg, UInt16 length);

	void	InteanalRecv(NetID net_id, char *msg, unsigned int length);

public:
	Thread	m_recv_client_thread;
	Thread	m_send_thread;

	NetID	m_game_net_id;
	NetID	m_login_net_id;
 

private:
	DatabaseFrame();

	TimeEventManager	m_time_event_manager;
	MessageHandler		m_message_handler;
	
};


#endif // FRAME_H
