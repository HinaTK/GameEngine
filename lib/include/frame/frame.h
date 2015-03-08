
#ifndef FRAME_H
#define FRAME_H

#include "libcommon/mutex.h"
#include "libcommon/thread.h"
#include "timemanager/timemanager.h"
#include "netmanager.h"

class Frame
{
public:
	Frame();
	virtual ~Frame();

	virtual	void		Recv(GameMsg *msg) = 0;

	virtual	void		Update(time_t now){};  //¸üÐÂ

	virtual void		Exit() = 0;

	void				UpdateAll();

	void				Send(NetHandle handle, const char *buf, unsigned int length);

	void				Listen();

	bool				Run();

	NetManager			*GetNetManager(){ return &m_net_manager; }

	void				SetUpdateInternal(int ms){ m_update_interval = ms; };

	void				SetExit(){ m_is_run = false; }

protected:
	unsigned long long	UpdateInternal(){ return m_update_interval; }
	NetManager			m_net_manager;
	TimeEventManager	m_time_manager;

private:
	
	Thread		m_listen_thread;
	Thread		m_log_thread;
	
	unsigned long long	m_update_interval;		// ºÁÃë
	bool		m_is_run;

};


#endif // !SCENEFRAME_H
