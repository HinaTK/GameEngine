
#ifndef WEB_LISTENER_H
#define WEB_LISTENER_H

#include "listener.h"
#include "lib/include/common/mutex.h"
/*
监听者，监听所有数据的读写状态
*/

class WebListener : public Listener
{
public:
	WebListener(NetManager *manager)
		: Listener(manager){}
	virtual ~WebListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);
protected:
	virtual int		AnalyzeBuf();

};

#endif // !WEB_LISTENER_H
