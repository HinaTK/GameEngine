
#ifndef LISTENER_H
#define LISTENER_H

#include "nethandler.h"
#include "bufmanager.h"
#include "netmanager.h"
#include "lib/include/common/mutex.h"

/*
	监听者，监听所有数据的读写状态
	虚基类
*/

class Listener : public NetHandler
{
	static const unsigned int BASE_BUFFER_LENGTH = 512;
public:
	Listener(SocketThread *t);
    virtual ~Listener();

	virtual void	OnCanRead();
	virtual void	OnCanWrite();

	virtual void	Send(const char *buf, unsigned int len) = 0;

	void			RegisterWriteFD();

protected:
	bool			RecvBuf();
	virtual bool	AnalyzeBuf() = 0;
	
	void			UnRegisterWriteFD();
protected:
	RecvBuffer	m_recv_buf;
	SendBuffer	*m_send_buf_read;	// 只读
	SendBuffer	*m_send_buf_write;	// 只写
	std::mutex	m_send_mutex;
	std::mutex	m_register_write_mutex;
    int         m_register_state;
};

#endif
