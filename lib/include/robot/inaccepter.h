
#ifndef IN_ACCEPTER_H
#define IN_ACCEPTER_H

#include "lib/include/frame/accepter.h"
/*
接收者，管理所有的请求链接
注：不作对象池管理，因为个数少且不会频繁分配与释放内存
*/

class INAccepter : public Accepter
{
public:
	INAccepter(SocketThread *t, int size = 0);
	virtual ~INAccepter(){}

	virtual void	OnCanRead();
private:
	int buf_size;
};

#endif