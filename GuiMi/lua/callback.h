
#ifndef CALL_BACK_H
#define CALL_BACK_H

#include "lib/include/frame/msgcallback.h"

class Interface;
class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(Interface *interface) : m_interface(interface){}
	~InnerCallBack(){}

	void	Accept(NetHandle handle, const char *ip);

	void	Recv(GameMsg *msg);

	void	Disconnect(NetHandle handle);

private:
	Interface *m_interface;
};

class OuterCallBack : public MsgCallBack
{
public:
	OuterCallBack(Interface *interface) : m_interface(interface){}
	~OuterCallBack(){}

	void	Accept(NetHandle handle, const char *ip);

	void	Recv(GameMsg *msg);

	void	Disconnect(NetHandle handle);

private:
	Interface *m_interface;
};

#endif
