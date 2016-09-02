
#include <string>
#include "dataupdate.h"
#include "lib/include/base/function.h"

static int traceback(lua_State *L) {
	const char *msg = lua_tostring(L, 1);
	if (msg)
	{
		luaL_traceback(L, L, msg, 1);
	}
	else 
	{
		lua_pushliteral(L, "(no error message)");
	}
	return 1;
}

DataUpdate::DataUpdate()
: m_L(NULL)
{
	
}

DataUpdate::~DataUpdate()
{
	if (m_L != NULL)
	{
		lua_close(m_L);
	}
}

bool DataUpdate::Init(char *file)
{
	m_L = luaL_newstate();
	luaL_openlibs(m_L);
	std::string path = Function::WorkDir() + file;
	if (luaL_loadfile(m_L, path.c_str()) || lua_pcall(m_L, 0, 0, 0))
	{
		Function::Error("%s", lua_tostring(m_L, -1));
		return false;
	}

	lua_pushcfunction(m_L, traceback);
	lua_getglobal(m_L, "OnUpdate");
	//lua_getglobal(m_L, "OnUpdate");
	// lua_pushstring(m_L, "test");
	// lua_pushstring(m_L, "{\"ver\"=1}");
	// lua_pushinteger(m_L, 1);
	// if (lua_pcall(m_L, 3, 2, 1) != LUA_OK)
	// {
	// 	Function::Error("lua call OnUpdate %s", lua_tostring(m_L, -1));
	// 	return false;
	// }
	return true;
}

char * DataUpdate::OnUpdate(char *module, int len, char *data)
{
	printf("xxxx1 %d\n", lua_gettop(m_L));
	lua_getglobal(m_L, "OnUpdate");
	lua_pushstring(m_L, module);
	lua_pushlstring(m_L, data, len);
	char *ret = NULL;
	if (lua_pcall(m_L, 2, 2, 1) == LUA_OK)
	{
		if (lua_toboolean(m_L, -2))
		{
			ret = (char *)lua_tostring(m_L, -1);
		}
		else
		{
			Function::Error("%s lua data update %s", module, lua_tostring(m_L, -1));
			lua_pop(m_L, 2);
		}
	}
	else
	{
		Function::Error("%s, OnUpdate %s", module, lua_tostring(m_L, -1));
		lua_pop(m_L, 1);
	}
	printf("xxxx2 %d\n", lua_gettop(m_L));
	return ret;
}

void DataUpdate::Release()
{
	lua_pop(m_L, 2);
}
