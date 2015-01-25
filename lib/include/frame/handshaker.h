
#ifndef HAND_SHAKER_H
#define HAND_SHAKER_H

#include "nethandler.h"

/*
	握手者 专门处理websocket的握手处理
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