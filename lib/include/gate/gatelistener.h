
#ifndef GATE_LISTENER_H
#define GATE_LISTENER_H

#include "lib/include/frame/listener.h"
/*
	监听者，监听所有数据的读写状态
*/

class GateListener;
class GateBuffer
{
public:
	GateBuffer(GateListener *listener);
	~GateBuffer();

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
	GateListener *	m_listener;
	char			m_head_len;
	char 			m_header[NetCommon::HEADER_LENGTH];
};


class GateListener : public Listener
{
public:
	GateListener(SocketThread *t, int size = 0);
	virtual ~GateListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);

protected:
	virtual bool	RecvBuf();
	
	GateBuffer	m_recv_buf;
};

#endif