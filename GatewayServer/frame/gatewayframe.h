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
 
    bool	Init();    //��ʼ��

	void	Update(unsigned int interval, time_t now);

	void	Exit();
	void	Wait();
	void	Recv(GameMsg *msg);



public:
	SOCKET	m_gate_net_id;
    SOCKET	m_game_server_net_id;
	SOCKET	m_global_server_net_id;
	SOCKET	m_login_server_net_id;

private:
	GatewayFrame();
	TimeEventManager	m_time_event_manager;

};


#endif
