
#ifndef BASE_LISTENER_H
#define BASE_LISTENER_H

#include "listener.h"
#include "bufmanager.h"
#include "lib/include/common/mutex.h"
/*
	监听者，监听所有数据的读写状态
*/

class BaseListener : public Listener
{
public:
	BaseListener(NetManager *manager)
		: Listener(manager)
		, m_is_tencent_pass(false){}
	virtual ~BaseListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);
protected:
	virtual bool	AnalyzeBuf();
	bool			m_is_tencent_pass;

};

#endif