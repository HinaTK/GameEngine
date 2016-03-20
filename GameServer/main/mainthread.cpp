
#include "mainthread.h"
#include "lib/include/thread/threadmanager.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/baselistener.h"

MainThread::MainThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void MainThread::Init(void *arg)
{

}

bool MainThread::Run()
{
	return false;
}

int db = 0;
int mm = 0;
struct qqq
{
	int id;
	int val;
};

void MainThread::RecvMsg(unsigned char sid, int len, const char *data)
{

}

