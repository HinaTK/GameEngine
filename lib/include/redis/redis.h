
#ifndef REDIS_H
#define REDIS_H

#include "common/socketdef.h"

class Redis
{
public:
	Redis();
	~Redis();

	void	SetNetHandle(NetHandle handle){ m_net_handle = handle; }


private:

	NetHandle	m_net_handle;
};

#endif