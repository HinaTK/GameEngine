
#ifndef LISTENER_H
#define LISTENER_H

#include "nethandler.h"
#include "bufmanager.h"
#include "netmanager.h"
#include "lib/include/common/mutex.h"

/*
	监听者，监听所有数据的读写状态
*/

class MsgCallBack;
class Listener : public NetHandler
{
	static const unsigned int BASE_BUFFER_LENGTH = 512;
public:
	Listener(NetManager *manager, MsgCallBack *call_back)
		: NetHandler(manager, NetHandler::LISTENER)
		, m_recv_buf(BASE_BUFFER_LENGTH)
		, m_send_buf_read(new SendBuffer(BASE_BUFFER_LENGTH))
		, m_send_buf_write(new SendBuffer(BASE_BUFFER_LENGTH))
		, m_is_register_write(false)
		, m_call_back_handle(manager->RegisterCallBack(call_back))
	{
	}
	virtual ~Listener()
	{
		if (m_send_buf_read != NULL)
		{
			delete m_send_buf_read;
			m_send_buf_read = NULL;
		}
		if (m_send_buf_write != NULL)
		{
			delete m_send_buf_write;
			m_send_buf_write = NULL;
		}
	}

	virtual void	OnCanRead();
	virtual void	OnCanWrite();

	virtual void	Send(const char *buf, unsigned int len);

	bool			IsRegisterWrite(){ return m_is_register_write; }
	void			RegisterWriteFD();

	int				GetCallBackHandle(){ return m_call_back_handle; }
protected:
	bool			RecvBuf();
	virtual bool	AnalyzeBuf() = 0;
	
	void			UnRegisterWriteFD();
protected:
	BufManager	m_recv_buf;
	SendBuffer	*m_send_buf_read;	// 只读
	SendBuffer	*m_send_buf_write;	// 只写
	bool		m_is_register_write;
	std::mutex	m_send_mutex;
	std::mutex	m_register_write_mutex;
	int			m_call_back_handle;
};

#endif