
#ifndef HAND_SHAKER_H
#define HAND_SHAKER_H

#include "nethandler.h"

/*
	握手者 专门处理websocket的握手处理
*/

class HandShaker : public NetHandler
{
public:
	HandShaker(NetManager *manager, int type) 
		: NetHandler(manager, type)
		, m_data_length(0)
		, m_send_length(0)
		, m_is_clear(false)
	{
		memset(m_handshake_data, 0, sizeof(m_handshake_data));
	};
	~HandShaker(){};

	virtual void	OnCanRead();
	virtual void	OnCanWrite();

	bool			IsClear(){ return m_is_clear; }
	void *		operator new(size_t c);
	void		operator delete(void *m);

protected:
	bool			HandShake();

	char			m_handshake_data[256];
	int				m_data_length;	// 数据长度
	int				m_send_length;	// 已经发送数据长度
	bool			m_is_clear;		// 握手错误，用于彻底删除套接字
};

#endif