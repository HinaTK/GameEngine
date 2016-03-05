
#ifndef CHAT_THREAD_H
#define CHAT_THREAD_H

/*
	��chatд��gateway
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
	void	RecvMsg(unsigned char sid, int len, const char *data);
private:
};

#endif