
#ifndef DATA_UPDATE_H
#define DATA_UPDATE_H

#include "export.h"
#include "lib/include/lua/luadef.h"

class DataUpdate
{
public:
	DataUpdate();
	~DataUpdate();

	bool	Init(char *file);
	char *	OnUpdate(const char *module, int len, char *data);
	void	Release();
private:
	lua_State *m_L;
};

namespace New
{
	EXPORT DataUpdate * _DataUpdate();
}
#endif