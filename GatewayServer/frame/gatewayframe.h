#ifndef GATEWAYFRAME
#define GATEWAYFRAME


#include "common/commonvariable.h"
#include "libcommon.h"
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

//	void	ExternalRecv(NetID net_id, char *msg, UInt16 length);

	void	InteanalRecv(NetID net_id, char *msg, UInt16 length);

	void	NetSend(NetID net_id, char *msg, UInt16 length);

	//virtual ExCom	*GetExCom(){ return &m_ex_com; }

public:
	NetID	m_gate_net_id;
    NetID	m_game_server_net_id;
	NetID	m_global_server_net_id;
	NetID	m_login_server_net_id;

protected:
	//ExCom				m_ex_com;

private:
	GatewayFrame();
	TimeEventManager	m_time_event_manager;

};


#endif
