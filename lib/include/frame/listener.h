
#ifndef LISTENER_H
#define LISTENER_H

#include "nethandler.h"
#include "bufmanager.h"
#include "libcommon/mutex.h"
/*
	�����ߣ������������ݵĶ�д״̬
*/

class Listener : public NetHandler
{
public:
	Listener(NetManager *manager, int type)
		: NetHandler(manager, type)
		, m_recv_buf(128)
		, m_send_buf_read(NULL)
		, m_send_buf_write(NULL)
		, m_is_register_write(false)
	{
		m_send_buf_read = new BufManager(128);
		m_send_buf_write = new BufManager(128);
	}
	virtual ~Listener()
	{
		if (m_send_buf_read != NULL)
		{
			delete m_send_buf_read;
		}
		if (m_send_buf_write != NULL)
		{
			delete m_send_buf_write;
		}
	}

	virtual void	OnCanRead();
	virtual void	OnCanWrite();

	virtual void	Send(const char *buf, unsigned int len) = 0;

	bool			IsRegisterWrite(){ return m_is_register_write; }
	void			RegisterWriteFD();


protected:
	bool			RecvBuf();
	virtual bool	AnalyzeBuf() = 0;
	
	void			UnRegisterWriteFD();
protected:
	BufManager	m_recv_buf;
	BufManager	*m_send_buf_read;	// ֻ��
	BufManager	*m_send_buf_write;	// ֻд
	bool		m_is_register_write;
	Mutex		m_send_mutex;
	Mutex		m_register_write_mutex;
};

#endif