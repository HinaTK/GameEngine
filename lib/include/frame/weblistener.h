
#ifndef WEB_LISTENER_H
#define WEB_LISTENER_H

#include "listener.h"
#include "bufmanager.h"
#include "libcommon/mutex.h"
/*
监听者，监听所有数据的读写状态
*/

class WebListener : public Listener
{
public:
	WebListener(NetManager *manager, int type): Listener(manager, type){}
	virtual ~WebListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

protected:
	virtual bool AnalyzeBuf();

};

#endif // !WEB_LISTENER_H
