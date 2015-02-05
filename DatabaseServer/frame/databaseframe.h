#ifndef DATABASEFRAME_H
#define DATABASEFRAME_H

#include "libtimemanager.h"
#include "frame/frame.h"
#include "message/messagehandler.h"

class DatabaseFrame : public Frame
{
public:

    ~DatabaseFrame();

    static DatabaseFrame &Instance()
    {
        static DatabaseFrame frame;
        return frame;
    }

	bool	InitConfig();

    bool	Init();    //初始化

 
    void	Update(time_t now);  //更新

    void	Exit();

	void	Recv(GameMsg *msg);

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
