
#ifndef LUA_TEST_H
#define LUA_TEST_H

#include "script/luascript.h"

namespace LuaTest
{
	void VariableSave()
	{
		if (!LuaScript::Instance().LoadLuaFile("luafile\\test.lua"))
		{
			printf("open error\n");
			return;
		}
		int num = 0;
		LuaScript::Instance().GlobalVariable("global_num", &num, LuaScript::INTEGER);
		printf("num = %d\n", num);
		LuaScript::Instance().GlobalFunction("SetGlobalNum", 0, 0);
		LuaScript::Instance().GlobalVariable("global_num", &num, LuaScript::INTEGER);
		printf("num = %d\n", num);
	}
}


#endif