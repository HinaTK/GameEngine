
#ifndef BASE_LISTENER_H
#define BASE_LISTENER_H

#include "listener.h"
#include "bufmanager.h"
#include "libcommon/mutex.h"
/*
	监听者，监听所有数据的读写状态
*/

class BaseListener : public Listener
{
public:
	BaseListener(NetManager *manager, int type): Listener(manager, type){}
	virtual ~BaseListener(){	}

	void *		operator new(size_t c);
	void		operator delete(void *m);

protected:
	virtual bool	AnalyzeBuf();

};

#endif