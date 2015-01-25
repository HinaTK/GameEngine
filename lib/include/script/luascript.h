
#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include "luadef.h"


class LuaScript
{
public:
	~LuaScript();

	static LuaScript &Instance()
	{
		static LuaScript script;
		return script;
	}

	enum
	{
		NIL,
		STRING,
		INTEGER,
		DOUBLE
	};

	

	bool			LoadLuaFile(std::string filename);

	lua_CFunction	GlobalFunction(const char *function_ame);

	bool			GlobalFunction(const char *function_ame, int nargs, int nresults, int errfunc = 0);

	void			GlobalVariable(const char *field, void *result, int type);

private:
	LuaScript();

	bool			InitLuaEnv();

private:
	

	lua_State	*m_lua_env;
};

#endif
