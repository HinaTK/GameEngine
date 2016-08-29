
#include <string>
#include "update.h"
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

DataUpdate::DataUpdate(char *file)
{
	m_L = luaL_newstate();
	luaL_openlibs(m_L);
}

DataUpdate::~DataUpdate()
{
	lua_close(m_L);
}

bool DataUpdate::Init(char *file)
{
	std::string path = Function::WorkDir() + file;
	if (luaL_loadfile(m_L, path.c_str()))
	{
		Function::Error("%s", lua_tostring(m_L, -1));
		return false;
	}

	lua_pushcfunction(m_L, traceback);
	if (lua_pcall(m_L, 0, 0, 1))
	{
		Function::Error("%s", lua_tostring(m_L, -1));
		return false;
	}
	return true;
}

char * DataUpdate::OnUpdate(char *module, char *data)
{
	lua_getglobal(m_L, "OnUpdate");
	lua_pushlstring(m_L, module);
	lua_pushlstring(m_L, data);
	char *ret = NULL;
	do
	{
		if (lua_pcall(m_L, 2, 1, 1))
		{
			Function::Error("OnUpdate %s", lua_tostring(m_L, -1));
			break;
		}

		// todo 测试传错误参数
		if (lua_tobool(m_L, -1))
		{
			ret = lua_tostring(m_L, -2);
		}
		else
		{
			Function::Error("lua update %s", lua_tostring(m_L, -2));
		}

	}while(false)

	lua_settop(m_L, 1); 	// 设置堆栈剩下一个元素traceback？
	return ret;
}