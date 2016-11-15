
#ifndef GAME_PROXY_H
#define GAME_PROXY_H

#include "common/datastructure/gamehash.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/thread/threadmanager.h"

class Query : public Frame
{
public:
	Query();
	virtual ~Query();

	static Query &Instance()
	{
		static Query frame;
		return frame;
	}
	bool	Init();    //≥ı ºªØ
	bool	Start();

	bool	Cmd(char *buf);
	void	Exit();
	void	Wait();

};

#endif