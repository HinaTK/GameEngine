
#ifndef INTERFACE_H
#define INTERFACE_H

#include "luadef.h"
#include "common/socketdef.h"

class Interface
{
public:
	Interface();
	~Interface();

	bool	LoadFile(const char *file);
	void	OnInit();
	void	OnUpdate(int interval, unsigned int now);

	void	OnAccept(NetHandle netid, const char *ip);
	void	OnRecv(NetHandle netid, const char *name, const char *data);
	void	OnDisconnect(NetHandle netid);

	void	OnInnerAccept(NetHandle netid, const char *ip);
	void	OnInnerRecv(NetHandle netid, const char *name, const char *data);
	void	OnInnerDisconnect(NetHandle netid);


private:
	lua_State *m_L;
};

#endif