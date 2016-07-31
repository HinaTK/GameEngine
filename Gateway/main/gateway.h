
#ifndef GATEWAY_H
#define GATEWAY_H

#include "common/datastructure/gamehash.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/thread/threadmanager.h"

class Gateway : public Frame
{
public:
	Gateway();
	virtual ~Gateway();

	static Gateway &Instance()
	{
		static Gateway frame;
		return frame;
	}
	bool	Init();    //≥ı ºªØ
	bool	Start();

	void	Exit();
	void	Wait();

};

#endif