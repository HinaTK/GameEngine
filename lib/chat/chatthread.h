
#ifndef CHAT_THREAD_H
#define CHAT_THREAD_H

/*
	½«chatÐ´½øgateway
*/
#include "lib/include/thread/basethread.h"

class ChatThread : public BaseThread
{
public:
	virtual ~ChatThread();
	ChatThread(ThreadManager *manager);

protected:
	void	Init();
	void	Run();
	void	RecvMsg(ThreadMsg *msg);
private:
};

#endif