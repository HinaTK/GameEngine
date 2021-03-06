
#ifndef INTERFACE_H
#define INTERFACE_H

#include "luadef.h"
#include "common/socketdef.h"
#include "callback.h"

class Interface
{
public:
	Interface();
	~Interface();

	bool	LoadFile(const char *file);
	void	OnTest();
	void	OnInit();
	void	OnUpdate(int interval, unsigned int now);

	void	OnAccept(NetHandle netid, const char *ip);
	void	OnRecv(NetHandle netid, unsigned int length, const char *data);
	void	OnDisconnect(NetHandle netid);

	void	OnInnerAccept(NetHandle netid, const char *ip);
	void	OnInnerRecv(NetHandle netid, unsigned int length, const char *data);
	void	OnInnerDisconnect(NetHandle netid);

	void	OnXXXAccept(NetHandle netid, const char *ip);
	void	OnXXXRecv(NetHandle netid, unsigned int length, const char *data);
	void	OnXXXDisconnect(NetHandle netid);

	OuterCallBack	*GetOuterCallBack(){ return &m_o_call_back; }
	InnerCallBack	*GetInnerCallBack(){ return &m_i_call_back; }
	XXXCallBack		*GetXXXCallBack(){ return &m_x_call_back; }
private:
	lua_State *m_L;

	OuterCallBack	m_o_call_back;
	InnerCallBack	m_i_call_back;
	XXXCallBack		m_x_call_back;
};

#endif