
#ifndef DATA_BASE_FRAME_H
#define DATA_BASE_FRAME_H

#include "lib/include/timemanager/timemanager.h"
#include "lib/include/frame/frame.h"
#include "callback.h"

class NewFrame : public Frame
{
public:

    virtual ~NewFrame();

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

	void	Recv(GameMsg *msg);

public:

	NetHandle	m_game_handle;
	NetHandle	m_login_handle;
 

private:
	NewFrame();

    InnerCallBack		m_i_call_back;
	
};


#endif // FRAME_H
