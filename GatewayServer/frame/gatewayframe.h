#ifndef GATEWAYFRAME
#define GATEWAYFRAME


#include "common/commonvariable.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/timemanager/timemanager.h"
#include "lib/include/frame/frame.h"

class GatewayFrame : public Frame
{
public:

    ~GatewayFrame();

    static GatewayFrame &Instance()
    {
        static GatewayFrame frame;
        return frame;
    }

	bool	InitConfig();
 
    bool	Init();    //初始化

    void	Update(time_t now);  //更新

	void	Exit();
	void	Wait();
	void	Recv(GameMsg *msg);



public:
	NetID	m_gate_net_id;
    NetID	m_game_server_net_id;
	NetID	m_global_server_net_id;
	NetID	m_login_server_net_id;

private:
	GatewayFrame();
	TimeEventManager	m_time_event_manager;

};


#endif
