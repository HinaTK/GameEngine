
#ifndef CENTER_H
#define CENTER_H

#include "common/datastructure/gamehash.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/thread/threadmanager.h"

class Center : public Frame
{
public:
	Center();
	~Center();

	static Center &Instance()
	{
		static Center frame;
		return frame;
	}
	bool	Init();    //≥ı ºªØ
	void	Start();

	void	Exit();
	void	Wait();
	void	Cmd(char *buf);
};

#endif