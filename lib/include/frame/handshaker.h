
#ifndef HAND_SHAKER_H
#define HAND_SHAKER_H

#include "nethandler.h"

/*
	������ ר�Ŵ���websocket�����ִ���
*/

class HandShaker : public NetHandler
{
public:
	HandShaker(NetManager *manager, MsgCallBack *	_call_back)
		: NetHandler(manager, NetHandler::HANDSHAKER)
		, call_back(_call_back)
		, m_data_length(0)
		, m_send_length(0)
	{
		memset(m_handshake_data, 0, sizeof(m_handshake_data));
	};
	~HandShaker(){};

	virtual void	OnCanRead();
	virtual void	OnCanWrite();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	MsgCallBack *	call_back;
protected:
	bool			HandShake();

	char			m_handshake_data[256];
	int				m_data_length;	// ���ݳ���
	int				m_send_length;	// �Ѿ��������ݳ���
};

#endif