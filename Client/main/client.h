
#ifndef GATEWAY_H
#define GATEWAY_H

#include "common/datastructure/gamehash.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/thread/threadmanager.h"

class Client : public Frame
{
public:
	Client();
	virtual ~Client();

	static Client &Instance()
	{
		static Client frame;
		return frame;
	}
	bool	Init();    //≥ı ºªØ
	void	Start();

	void	Cmd(char *buf);
	void	Exit();
	void	Wait();

};

#endif