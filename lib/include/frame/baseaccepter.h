
#ifndef BASE_ACCEPTER_H
#define BASE_ACCEPTER_H

#include "accepter.h"

/*
	接收者，管理所有的请求链接
	注：不作对象池管理，因为个数少且不会频繁分配与释放内存
*/

class BaseAccepter : public Accepter
{
public:
	BaseAccepter(NetManager *manager, int size = 0);
    virtual ~BaseAccepter(){}

	virtual void	OnCanRead();
private:
	int buf_size;
};

#endif
