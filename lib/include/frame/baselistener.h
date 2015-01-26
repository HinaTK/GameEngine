
#ifndef BASE_LISTENER_H
#define BASE_LISTENER_H

#include "listener.h"
#include "bufmanager.h"
#include "libcommon/mutex.h"
/*
	�����ߣ������������ݵĶ�д״̬
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