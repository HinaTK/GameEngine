
#include "interface.h"
#include "chatthread.h"

void * NewChatThread(ThreadManager *manager)
{
	return new ChatThread(manager);
}

