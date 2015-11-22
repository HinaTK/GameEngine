
#ifndef INNER_ACCEPTER_H
#define INNER_ACCEPTER_H

// #include "nethandler.h"
// 
// /*
// 接收者，管理所有的请求链接
// 注：不作对象池管理，因为个数少且不会频繁分配与释放内存
// */
// class BaseListener;
// class InnerAccepter : public NetHandler
// {
// public:
// 	InnerAccepter(NetManager *manager, char *_ip, BaseListener *_listener)
// 		: NetHandler(manager, NetHandler::INNER_ACCEPTER)
// 		, ip(inet_addr(_ip))
// 		, linster(_listener)
// 	{
// 	}
// 	~InnerAccepter(){};
// 
// 	virtual void	OnCanRead();
// 
// 	unsigned long	ip;
// 	BaseListener	*linster;
// private:
// 
// };

#endif