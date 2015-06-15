
#ifndef REDIS_H
#define REDIS_H

#include "common/socketdef.h"

class Redis
{
public:
	Redis();
	~Redis();

	void	SetNetHandle();
private:

	SOCKET	m_net_handle;
};

#endif