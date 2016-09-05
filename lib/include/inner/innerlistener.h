
#ifndef INNER_LISTENER_H
#define INNER_LISTENER_H

#include "lib/include/frame/listener.h"
#include "lib/include/frame/bufmanager.h"
#include "lib/include/common/mutex.h"
/*
	监听者，监听所有数据的读写状态
*/

class InnerListener;
class InnerBuffer
{
public:
	InnerBuffer(InnerListener *listener);
	~InnerBuffer();

	bool		GetBufInfo(char **buf, int &len);
	int			AddBufLen(int len);

protected:
	void		ResetBuf();
private:
	struct GateMsg
	{
		unsigned short buf_len = 0;		// 容器长度
		unsigned short cur_len = 0;		// 数据长度
		unsigned short msg_len = 0;		// 消息总长度
		char *buf = NULL;
	}m_msg;
	InnerListener *	m_listener;
};

class InnerListener : public Listener
{
public:
	InnerListener(SocketThread *t, int size = 0);
	virtual ~InnerListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);

	int				buf_size;
protected:
	virtual bool	RecvBuf();
	
	InnerBuffer		m_recv_buf;
};

#endif