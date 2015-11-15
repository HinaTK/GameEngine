
#ifndef WEB_LISTENER_H
#define WEB_LISTENER_H

#include "listener.h"
#include "bufmanager.h"
#include "lib/include/common/mutex.h"
/*
�����ߣ������������ݵĶ�д״̬
*/

class WebListener : public Listener
{
public:
	WebListener(NetManager *manager, MsgCallBack *call_back) 
		: Listener(manager, new RecvMsg(call_back)){}
	virtual ~WebListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);
protected:
	virtual bool AnalyzeBuf();

};

#endif // !WEB_LISTENER_H
