
#include "mainthread.h"
#include "lib/include/thread/threadmanager.h"
#include "lib/include/common/serverconfig.h"
#include "lib/include/frame/baselistener.h"

MainThread::MainThread(ThreadManager *manager)
: BaseThread(manager)
{

}

void MainThread::Init()
{

}

void MainThread::Run()
{
	
}

int db = 0;
int mm = 0;
struct qqq
{
	int id;
	int val;
};
void MainThread::RecvMsg(ThreadMsg *msg)
{
	qqq ret = *(qqq *)msg->data;
	if (ret.id == ThreadManager::ID_DB)
	{
		if (db != ret.val)
		{
			printf("db MainThread ... %d \n", ret.val);
		}
		else if (ret.val >= 1000000)
		{
			printf("db end \n");
		}
		++db;
	}
	else
	{
		if (mm != ret.val)
		{
			printf("mm MainThread ... %d \n", ret.val);
		}
		else if (ret.val >= 1000000)
		{
			printf("mm end \n");
		}
		++mm;
	}
}

