
#ifndef HAND_SHAKER_H
#define HAND_SHAKER_H

#include "nethandler.h"

/*
	������ ר�Ŵ���websocket�����ִ���
*/

class HandShaker : public NetHandler
{
public:
	HandShaker(NetManager *manager, int type) : NetHandler(manager, type){};
	~HandShaker(){};

	virtual void	OnCanRead();

	void *		operator new(size_t c);
	void		operator delete(void *m);

protected:

	bool		HandShake();
};

#endif