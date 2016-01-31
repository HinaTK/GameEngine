
#ifndef CALL_BACK_H
#define CALL_BACK_H

#include "lib/include/frame/msgcallback.h"

class Interface;
class XXXCallBack : public MsgCallBack
{
public:
	XXXCallBack(Interface *interface) : m_interface(interface){}
	~XXXCallBack(){}

	void	Accept(NetHandle handle, const char *ip);

	void	Recv(GameMsg *msg);

	void	Disconnect(NetHandle handle, int reason);

private:
	Interface *m_interface;
};

class InnerCallBack : public MsgCallBack
{
public:
	InnerCallBack(Interface *interface) : m_interface(interface){}
	~InnerCallBack(){}

	void	Accept(NetHandle handle, const char *ip);

	void	Recv(GameMsg *msg);

	void	Disconnect(NetHandle handle, int reason);

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

	void	Disconnect(NetHandle handle, int reason);

private:
	Interface *m_interface;
};

#endif
