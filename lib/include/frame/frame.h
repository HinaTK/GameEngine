
#ifndef FRAME_H
#define FRAME_H

#include "netmanager.h"
#include "lib/include/timemanager/timemanager.h"
#include "lib/include/log/logmanager.h"


class BaseCallBack;
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

	void				SetFPS(int ms);

	void				SetExit();

	bool				IsRun(){ return m_is_run; }

protected:
	NetManager			m_net_manager;
	TimeEventManager	m_time_event_manager;
	LogManager			m_log_manager;
	unsigned int		m_sleep_time_ms;
	BaseCallBack		*m_call_back;
private:
	bool		m_is_run;

};



#endif // !SCENEFRAME_H
