
#ifndef GAME_PROXY_H
#define GAME_PROXY_H

#include "common/datastructure/gamehash.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/thread/threadmanager.h"

class Proxy : public Frame
{
public:
	Proxy();
	virtual ~Proxy();

	static Proxy &Instance()
	{
		static Proxy frame;
		return frame;
	}
	bool	Init();    //≥ı ºªØ
	bool	Start();

	bool	Cmd(char *buf);
	void	Exit();
	void	Wait();

};

#endif