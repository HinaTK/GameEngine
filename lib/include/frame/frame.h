﻿
#ifndef FRAME_H
#define FRAME_H

#include "lib/include/thread/threadmanager.h"

class Frame;

typedef void(*CmdFun)(Frame *frame, char *buf);
class Frame
{
public:
	Frame();
	virtual ~Frame();

	virtual void		Exit() = 0;
	virtual	void		Wait() = 0;
	virtual	void		Cmd(char *buf) = 0;

	void				Run();
	void				SetExit();
	bool				IsRun(){ return m_is_run; }

	

protected:
	ThreadManager		m_thread_manager;
private:
	bool		m_is_run;

};



#endif // !SCENEFRAME_H
