
#ifndef FRAME_H
#define FRAME_H

#include "lib/include/timemanager/timemanager.h"
#include "accepter.h"
#include "webaccepter.h"
#include "listener.h"
#include "baselistener.h"


class BaseCallBack;
class Frame
{
public:
	Frame();
	virtual ~Frame();

	virtual bool		Init();

	virtual	void		Update(unsigned int interval, time_t now) = 0;  //更新

	virtual void		Exit() = 0;

	virtual	void		Wait() = 0;
	virtual	void		Loop() = 0;

	void				UpdateAll(unsigned long long interval);
	
	bool				Run();

	void				SetFPS(int ms);

	void				SetExit();

	bool				IsRun(){ return m_is_run; }

protected:
	TimeEventManager	m_time_event_manager;
	unsigned int		m_sleep_time_ms;
private:
	bool		m_is_run;

};



#endif // !SCENEFRAME_H
