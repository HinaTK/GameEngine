
#ifndef FRAME_H
#define FRAME_H

#include "libcommon/mutex.h"
#include "libcommon/thread.h"
#include "netmanager.h"

class Frame
{
public:
	Frame();
	virtual ~Frame();

	virtual	void		Recv(GameMsg *msg) = 0;

	virtual	void		Update(time_t now){};  //¸üÐÂ

	virtual void		Accept(NetID net_id){};

	virtual void		DisConnet(NetID net_id){};

	void				Send(NetHandle handle, const char *buf, unsigned int length);

	void				Listen();

	bool				Run();

	NetManager			*GetNetManager(){ return &m_net_manager; }

	void				SetUpdateInternal(int ms){ m_update_interval = ms; };


protected:
	unsigned long long	UpdateInternal(){ return m_update_interval; }
	NetManager		m_net_manager;

private:
	
	Thread		m_recv_external_thread;
	Thread		m_send_external_thread;
	Thread		m_send_internal_thread;
	Thread		m_listen_thread;
	Thread		m_log_thread;
	
	unsigned long long	m_update_interval;		// ºÁÃë

};


#endif // !SCENEFRAME_H
