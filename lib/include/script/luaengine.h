
#ifndef LUA_ENGINE_H
#define LUA_ENGINE_H

#include <string>
#include "luadef.h"

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
	~LuaEngine();
    bool LoadLuaFile(std::string fileName);

    lua_State * GetLuaState()
    {
        return m_L;
    };

    void    PushString(std::string str);

    void    PushInt(int data);

    void    PushDouble(double data);

    bool    GetGlobalProc(const char *func, int arg = 0, int result = 0);       //调用lua函数

    int     GetGlobalVar(char *field, void **result/*,int type = NULLDATA*/);                             //获得全局变量

    void    GetGlobalVar(char *field, void *result, int dataType);

    void    DeleteGlobalVar(unsigned int dataType, void *field = NULL);

    int     GetResult(int index, void **result/*,int type = NULLDATA*/);

    void    GetResult(int index, void *result, int dataType);

    void    SetGlobalVar(char *field, void *var, int dataType);

    void    GetGlobalTable(char *field, int key, void **result);

    void    GetGlobalTable(char *field, int key, void *result, int dataType);

private:
    lua_State * m_L;
	std::string m_lua_file;
};

#endif // LUAENGINE_H
