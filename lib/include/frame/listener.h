﻿
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
	Listener(SocketThread *t, int size = 0);
    virtual ~Listener();

	virtual void	OnCanRead();
	virtual void	OnCanWrite();

	virtual void	Send(const char *buf, unsigned int len) = 0;

	void			RegisterWriteFD();

	int				buf_size;	// 限定的包大小
protected:
	virtual bool	RecvBuf();
	virtual bool	AnalyzeBuf(){ return true; };
	
	void			UnRegisterWriteFD();
protected:
	SendBuffer	*m_send_buf;
	std::mutex	m_register_write_mutex;
    int         m_register_state;
	
};

#define RETUEN_ERROR(Err)\
	m_err = Err; \
	return false;

#define RETUEN_ERROR_2(Err, Arg)\
	m_err = Err; \
	m_err_arg = Arg;\
	return false;

#endif

