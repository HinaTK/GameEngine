
#ifndef ACCEPTER_H
#define ACCEPTER_H

#include "nethandler.h"

/*
	接收者，管理所有的请求链接
	注：不作对象池管理，因为个数少且不会频繁分配与释放内存
*/
class Listener;
class Accepter : public NetHandler
{
public:
	Accepter(NetManager *manager, MsgCallBack *call_back, int type = NetHandler::ACCEPTER)
		: NetHandler(manager, type, new AcceptMsg(call_back))
	{

	}
	~Accepter(){};

	virtual void	OnCanRead();
};

#endif