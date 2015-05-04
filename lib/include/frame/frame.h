
#ifndef FRAME_H
#define FRAME_H

#include "lib/include/common/mutex.h"
#include "lib/include/common/thread.h"
#include "lib/include/timemanager/timemanager.h"
#include "lib/include/log/logmanager.h"
#include "netmanager.h"

class Frame
{
public:
	Frame();
	virtual ~Frame();

	virtual bool		Init();

	virtual	void		Recv(GameMsg *msg) = 0;

	virtual	void		Update(unsigned int interval, time_t now) = 0;  //¸üÐÂ

	virtual void		Exit() = 0;

	virtual	void		Wait() = 0;

	void				UpdateAll(unsigned long long interval);

	void				Send(NetHandle handle, const char *buf, unsigned int length);

	bool				Run();

	NetManager			*GetNetManager(){ return &m_net_manager; }
	LogManager			*GetLogManager(){ return &m_log_manager; }

	void				SetUpdateInternal(int ms){ m_FPS = ms; };

	void				SetExit();

	bool				IsRun(){ return m_is_run; }

protected:
	NetManager			m_net_manager;
	TimeEventManager	m_time_event_manager;
	LogManager			m_log_manager;

	unsigned long long	m_FPS;		// ºÁÃë
	unsigned int		m_sleep_time_ms;
private:
	
	Thread		m_listen_thread;
	Thread		m_log_thread;
	
	
	bool		m_is_run;

};


#endif // !SCENEFRAME_H
