

#ifndef CHAT_INTERFACE_H
#define CHAT_INTERFACE_H

class ThreadManager;
_declspec(dllexport) void * NewChatThread(ThreadManager *manager);

#endif