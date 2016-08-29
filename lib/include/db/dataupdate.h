
#ifndef DATA_UPDATE_H
#define DATA_UPDATE_H

#include "luadef.h"

class DataUpdate
{
public:
	DataUpdate(char *file);
	~DataUpdate();

	bool	Init(char *file);
	char *	OnUpdate(char *module, char *data);
private:
	lua_State *m_L;
};

#endif