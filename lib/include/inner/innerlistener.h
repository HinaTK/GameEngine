﻿
#ifndef INNER_LISTENER_H
#define INNER_LISTENER_H

#include "lib/include/frame/listener.h"
#include "lib/include/frame/bufmanager.h"
#include "lib/include/common/mutex.h"
/*
	监听者，监听所有数据的读写状态
*/


class InnerListener : public Listener
{
public:
	InnerListener(SocketThread *t, int size = 0);
	virtual ~InnerListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

protected:
	virtual bool	RecvBuf();
	
	RecvBuffer		m_recv_buf;
};

#endif