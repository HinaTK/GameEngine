
#ifndef CENTER_H
#define CENTER_H

#include "common/datastructure/gamehash.h"
#include "common/serverdef.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/thread/threadmanager.h"

class Center : public Frame
{
public:
	
	~Center();

	static const int MAX_DB_THREAD = 2;
	static Center &Instance()
	{
		static Center frame;
		return frame;
	}


	bool	Init();    //≥ı ºªØ
	bool	Start();

	void	Exit();
	void	Wait();
	bool	Cmd(char *buf);

	ThreadID 	db_thread_id[MAX_DB_THREAD];
private:
	Center();
};

#endif