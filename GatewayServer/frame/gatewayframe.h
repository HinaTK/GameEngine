#ifndef GATEWAYFRAME
#define GATEWAYFRAME


#include "common/commonvariable.h"
#include "libcommon/serverconfig.h"
#include "libtimemanager.h"
#include "frame/frame.h"

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
