
#ifndef ACCEPTER_H
#define ACCEPTER_H

#include "nethandler.h"

/*
	接收者，管理所有的请求链接
	注：不作对象池管理，因为个数少且不会频繁分配与释放内存
*/

class Accepter : public NetHandler
{
public:
	Accepter(SocketThread *t, int type);
	~Accepter(){};

	virtual void	OnCanRead() = 0;
};

#endif