
#ifndef NET_USER_H
#define NET_USER_H

#include "bufmanager.h"
#include "common/systemdef.h"


class NetUser
{
public:
	~NetUser(){};
	NetUser(NetID net_id) :m_net_id(net_id)
	{};

	/* 
		��Ҫʹ��BufManager	&GetBufManager(){ return m_buf_manager; }
		��Ϊ������ʹ��ʱ,BufManager manager = GetBufManager();����ǰ����
	*/
	BufManager	*GetBufManager(){ return &m_buf_manager; }		

	NetID		GetNetID(){ return m_net_id; }

	void *		operator new(size_t c);
	void		operator delete(void *m);

private:
	BufManager	m_buf_manager;
	NetID		m_net_id;
};


#endif