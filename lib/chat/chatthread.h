
#ifndef CHAT_THREAD_H
#define CHAT_THREAD_H

/*
	½«chatÐ´½øgateway
*/
#include "lib/include/thread/basethread.h"

//class ChatThread : public BaseThread
class ChatThread
{
public:
	virtual ~ChatThread();
	ChatThread(ThreadManager *manager);

protected:
	void	Init();
	bool	Run();
	void	RecvMsg(unsigned char sid, int len, const char *data);
private:
};

#endif