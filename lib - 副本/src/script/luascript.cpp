
#include <string.h>
#include "script/luascript.h"

LuaScript::LuaScript()
: m_lua_env(NULL)
{
	InitLuaEnv();
}

LuaScript::~LuaScript()
{
}


bool LuaScript::InitLuaEnv()
{
	m_lua_env = luaL_newstate();
	luaopen_base(m_lua_env);
	luaL_openlibs(m_lua_env);
	return true;
}

bool LuaScript::LoadLuaFile(std::string filename)
{
	int result = luaL_loadfile(m_lua_env, filename.c_str());
	if (result)
	{
		return false;
	}
	result = lua_pcall(m_lua_env, 0, 0, 0);
	return result == 0;
}

lua_CFunction LuaScript::GlobalFunction(const char *function_ame)
{
	lua_getglobal(m_lua_env, function_ame);
	if (!lua_isfunction(m_lua_env, 1))
	{
		return NULL;
	}

	return lua_tocfunction(m_lua_env, 1);
}

bool LuaScript::GlobalFunction(const char *function_ame, int nargs, int nresults, int errfunc /*= 0*/)
{
	lua_getglobal(m_lua_env, function_ame);
	if (!lua_isfunction(m_lua_env, 1))
	{
		return false;
	}
	lua_tocfunction(m_lua_env, 1);
	lua_pcall(m_lua_env, nargs, nresults, errfunc);
	return true;
}

void LuaScript::GlobalVariable(const char *field, void *result, int type)
{
	lua_pcall(m_lua_env, 0, 0, 0);

	lua_getglobal(m_lua_env, field);
	if (type == STRING)
	{
		memcpy(result, lua_tostring(m_lua_env, -1), strlen(lua_tostring(m_lua_env, -1)));
	}
	else if (type == INTEGER)
	{
		int i_temp = lua_tointeger(m_lua_env, -1);
		memcpy(result, &i_temp, sizeof(int));
	}
	else if (type == DOUBLE)
	{
		double d_temp = lua_tonumber(m_lua_env, -1);
		memcpy(result, &d_temp, sizeof(double));
	}
}
