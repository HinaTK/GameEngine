
#ifndef LUA_ENGINE_H
#define LUA_ENGINE_H


extern "C"
{
    #include "lua/lua.h"
    #include "lua/lualib.h"
    #include "lua/lauxlib.h"
};

#include <string>

class LuaEngine
{
public:
    enum datatype
    {
        NULLDATA = -1,
        STRING,
        INTEGER,
        DOUBLE
    };
    LuaEngine();
    bool LoadLuaFile(std::string fileName);
    lua_State * InitLuaEnv();

    lua_State * GetLuaEnv()
    {
        return m_state;
    };

    void    PushString(std::string str);

    void    PushInt(int data);

    void    PushDouble(double data);

    bool    GetGlobalProc(const std::string& procName, int arg, int result);       //调用lua函数

    int     GetGlobalVar(char *field, void **result/*,int type = NULLDATA*/);                             //获得全局变量

    void    GetGlobalVar(char *field, void *result, int dataType);

    void    DeleteGlobalVar(unsigned int dataType, void *field = NULL);

    int     GetResult(int index, void **result/*,int type = NULLDATA*/);

    void    GetResult(int index, void *result, int dataType);

    void    SetGlobalVar(char *field, void *var, int dataType);

    void    GetGlobalTable(char *field, int key, void **result);

    void    GetGlobalTable(char *field, int key, void *result, int dataType);

private:
    lua_State * m_state;
	std::string m_luafile;
};

#endif // LUAENGINE_H
