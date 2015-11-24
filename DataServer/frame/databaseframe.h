
#ifndef DATA_BASE_FRAME_H
#define DATA_BASE_FRAME_H

#include "lib/include/timemanager/timemanager.h"
#include "lib/include/frame/frame.h"
#include "message/messagehandler.h"

class InnerCallBack;
class DatabaseFrame : public Frame
{
public:

    virtual ~DatabaseFrame();

    static DatabaseFrame &Instance()
    {
        static DatabaseFrame frame;
        return frame;
    }

	bool	InitConfig();

    bool	Init();    //初始化

 
	void	Update(unsigned int interval, time_t now);  //更新

    void	Exit();

	void	Wait();

	void	Recv(GameMsg *msg);

public:
	Thread		m_recv_client_thread;
	Thread		m_send_thread;

	NetHandle	m_game_handle;
	NetHandle	m_login_handle;
 

private:
	DatabaseFrame();
	MessageHandler		m_message_handler;

	InnerCallBack		*m_i_call_back;
	
};


#endif // FRAME_H
