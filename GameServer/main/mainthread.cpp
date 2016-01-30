﻿
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

int mm = 0;
void MainThread::RecvMsg(ThreadMsg *msg)
{
	int ret = *(int *)msg->data;
	if (mm != ret)
	{
		printf("MainThread ... %d \n", ret);
	}
	else if (ret >= 10000)
	{
		printf("end \n");
	}
	++mm;
}

