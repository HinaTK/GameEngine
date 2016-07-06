
#include "chatthread.h"
#include "lib/include/thread/threadmanager.h"


ChatThread::~ChatThread()
{

}


// ChatThread::ChatThread(ThreadManager *manager)
// : BaseThread(manager)
ChatThread::ChatThread(ThreadManager *manager)
{

}

void ChatThread::Init()
{

}

int dbi = 0;
bool ChatThread::Run()
{
	return false;
}

void ChatThread::RecvMsg(unsigned char sid, int len, const char *data)
{
	printf("ChatThread ......... %d\n", *(int*)data);
}


