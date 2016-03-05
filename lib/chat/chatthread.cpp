
#include "chatthread.h"
#include "lib/include/thread/threadmanager.h"


ChatThread::~ChatThread()
{

}

ChatThread::ChatThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void ChatThread::Init()
{

}

int dbi = 0;
void ChatThread::Run()
{

}

void ChatThread::RecvMsg(unsigned char sid, int len, const char *data)
{
	printf("ChatThread ......... %d\n", *(int*)data);
}


