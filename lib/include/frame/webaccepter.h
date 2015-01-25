
#ifndef WEB_ACCEPTER_H
#define WEB_ACCEPTER_H

#include "nethandler.h"

class WebAccepter : public NetHandler
{
public:
	WebAccepter(NetManager *manager, int type) : NetHandler(manager, type){};
	~WebAccepter(){};

	virtual void	OnCanRead();

	void *		operator new(size_t c);
	void		operator delete(void *m);
protected:


};

#endif