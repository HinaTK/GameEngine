
#ifndef THREAD_EQPOLL_H
#define THREAD_EQPOLL_H

#include "threadnet.h"

class SocketThread : public ThreadNet
{
public:
	static const MAX_EPOLL_SIZE = 1024;
	
	virtual ~SocketThread();
	SocketThread(ThreadManager *manager, void *arg);

	void			SetCanWrite(NetHandler *handler);
	void			SetCanNotWrite(NetHandler *handler);

protected:
	bool			Run();
	
	void			ClearHandler();
	void			InitNetHandler(NetHandler *handler);

private:
	SOCKET				m_epoll_fd;
	struct epoll_event 	m_events[MAX_EPOLL_SIZE];
};

#endif
