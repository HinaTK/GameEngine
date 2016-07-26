
#ifndef THREAD_EQPOLL_H
#define THREAD_EQPOLL_H

#include "threadnet.h"

class SocketThread : public ThreadNet
{
public:
    static const int MAX_EPOLL_SIZE = 1024;
	
	virtual ~SocketThread();
    SocketThread(ThreadManager *manager, NetManager *net_manager);

	void			SetCanWrite(NetHandler *handler);
	void			SetCanNotWrite(NetHandler *handler);

protected:
	bool			Run();
	void			CMD(short type, ThreadID sid, int len, const char *data);
	void			ClearHandler();
	void			InitNetHandler(NetHandler *handler);

private:
	SOCKET				m_epoll_fd;
	struct epoll_event 	m_events[MAX_EPOLL_SIZE];
};

#endif
