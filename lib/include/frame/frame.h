
#ifndef FRAME_H
#define FRAME_H

#include "lib/include/thread/threadmanager.h"

class Frame;

class Frame
{
public:
	Frame();
	virtual ~Frame();

	virtual void		Exit() = 0;
	virtual	void		Wait() = 0;
	virtual	bool		Cmd(char *buf){ return false; };

	void				Run();
	void				SetExit();
	bool				IsRun(){ return m_is_run; }

protected:
	ThreadManager		m_thread_manager;
private:
	bool		m_is_run;

};



#endif // !SCENEFRAME_H
