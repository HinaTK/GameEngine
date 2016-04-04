
#include "mainthread.h"
#include "lib/include/thread/threadmanager.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/baselistener.h"

MainThread::MainThread(ThreadManager *manager)
: BaseThread(manager, NULL, ThreadManager::EXIT_NORMAL)
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

void MainThread::RecvData(short type, int sid, int len, const char *data)
{

}

