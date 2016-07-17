
#ifndef IN_LISTENER_H
#define IN_LISTENER_H

#include "lib/include/frame/listener.h"
#include "lib/include/frame/bufmanager.h"
#include "lib/include/common/mutex.h"
/*
监听者，监听所有数据的读写状态
*/

class INListener : public Listener
{
public:
	INListener(SocketThread *t, int size = 0);
	virtual ~INListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);

	int				buf_size;
protected:
	virtual bool	RecvBuf();
	virtual bool	AnalyzeBuf();

	BufManager	m_recv_buf;
};

#endif