
#ifndef HAND_SHAKER_H
#define HAND_SHAKER_H

#include "nethandler.h"

/*
	������ ר�Ŵ���websocket�����ִ���
*/

class HandShaker : public NetHandler
{
public:
	HandShaker(NetManager *manager, int type) 
		: NetHandler(manager, type)
		, m_data_length(0)
		, m_send_length(0)
		, m_is_remove(false)
	{
		memset(m_handshake_data, 0, sizeof(m_handshake_data));
	};
	~HandShaker(){};

	virtual void	OnCanRead();
	virtual void	OnCanWrite();

	bool			IsRemove(){ return m_is_remove; }

	void *		operator new(size_t c);
	void		operator delete(void *m);

protected:
	bool			HandShake();

	char			m_handshake_data[256];
	int				m_data_length;	// ���ݳ���
	int				m_send_length;	// �Ѿ��������ݳ���
	bool			m_is_remove;		// ���ִ������ڳ���ɾ���׽���
};

#endif