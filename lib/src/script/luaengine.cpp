
#include <string.h>
#include "script/luaengine.h"
#include "common/commonfunction.h"


LuaEngine::LuaEngine()
: m_lua_file("")
{
	m_L = luaL_newstate();
	luaL_openlibs(m_L);
}


LuaEngine::~LuaEngine()
{
	lua_close(m_L);
}

static int pcall_handler(lua_State* L)
{
	lua_getglobal(L, "debug");
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		return 1;
	}
	lua_getfield(L, -1, "traceback");
	if (!lua_isfunction(L, -1)) {
		lua_pop(L, 2);
		return 1;
	}
	lua_pushvalue(L, 1);
	lua_pushinteger(L, 2);
	lua_call(L, 2, 1);
	return 1;
}

static int traceback(lua_State *L) {
	const char *msg = lua_tostring(L, 1);
	if (msg)
		luaL_traceback(L, L, msg, 1);
	else {
		lua_pushliteral(L, "(no error message)");
	}
	return 1;
}

bool LuaEngine::LoadLuaFile(std::string file_name)
{
	if (m_lua_file != "")
	{
		return false;
	}
	m_lua_file = Function::WorkDir() + file_name;
	if (luaL_loadfile(m_L, m_lua_file.c_str()) || lua_pcall(m_L, 0, 0, 0))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return false;
	}

    return true;
}

void LuaEngine::PushString(std::string str)
{
    lua_pushstring(m_L,str.c_str());
}


void LuaEngine::PushInt(int data)
{
    lua_pushinteger(m_L,data);
}

void LuaEngine::PushDouble(double data)
{
    lua_pushnumber(m_L,data);
}

// 获取全局函数.
bool LuaEngine::GetGlobalProc(const char *func, int arg, int result)
{
	lua_pushcfunction(m_L, traceback);
	lua_getglobal(m_L, func);
    if (!lua_isfunction(m_L, -1))
    {
		lua_pop(m_L, 1);
        return false;
    }

	if (lua_pcall(m_L, arg, result, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return false;
	}
    return true;
}



void LuaEngine::GetGlobalVar(char *field, void *result, int type)
{
    lua_pcall(m_L,0,0,0);

    lua_getglobal(m_L,field);
    if (type == STRING)
    {
        memcpy(result,lua_tostring(m_L,-1),strlen(lua_tostring(m_L,-1)));
    }
    else if (type == INTEGER)
    {
        int i_temp = lua_tointeger(m_L,-1);
        memcpy(result,&i_temp,sizeof(int));
    }
    else if (type == DOUBLE)
    {
        double d_temp = lua_tonumber(m_L,-1);
        memcpy(result,&d_temp,sizeof(double));
    }

}

// 获取全局变量
//可用于读取配置
//lua_isstring 是否能转换成字符串

int LuaEngine::GetGlobalVar( char *field, void **result/*,int type = NULLDATA*/ )
{
	lua_pcall(m_L,0,0,0);

	lua_getglobal(m_L,field);
	int i_temp = 0;
	double d_temp = 0.0;
	if (lua_isnumber(m_L,-1))
	{
		i_temp=lua_tointeger(m_L,-1);
		d_temp=lua_tonumber(m_L,-1);
		if ((d_temp - i_temp) > 0)
		{
			*result = new double;
			memcpy(*result, &d_temp, sizeof(double));
			return LuaEngine::DOUBLE;
		}
		*result = new int;
		memcpy(*result, &i_temp, sizeof(int));
		return LuaEngine::INTEGER;
	}
	else if (lua_isstring(m_L,-1))
	{
		unsigned int lenght = 0;
		lenght = strlen(lua_tostring(m_L,-1));
		*result = new char[lenght];
		memcpy(*result,lua_tostring(m_L,-1),lenght);
		((char*)*result)[lenght] = '\0';
		return LuaEngine::STRING;
	}
	return LuaEngine::NULLDATA;
}




//注意index必为负数
int LuaEngine::GetResult(int index, void **result/*,int type*/)
{
    //char *c_temp;
    int i_temp;
    double d_temp;
    if (lua_isnumber(m_L,index))
    {
        i_temp=lua_tointeger(m_L,index);
        d_temp=lua_tonumber(m_L,index);
        if ((d_temp - i_temp) > 0)
        {
            *result = new double;
            memcpy(*result,&d_temp,sizeof(double));
            return DOUBLE;
        }
        *result = new int;
        memcpy(*result,&i_temp,sizeof(int));
        return INTEGER;
    }
    else if (lua_isstring(m_L,index))
    {
        unsigned int lenght = 0;
        lenght = strlen(lua_tostring(m_L,index));
        *result = new char[lenght];
        memcpy(*result,lua_tostring(m_L,index),lenght);
        ((char*)*result)[lenght] = '\0';
        return STRING;
    }
    return NULLDATA;
}


void LuaEngine::GetResult(int index, void *result, int dataType)
{
    if (dataType == STRING)
    {
        memcpy(result,lua_tostring(m_L,index),strlen(lua_tostring(m_L,index)));
    }
    else if (dataType == INTEGER)
    {
        int i_temp = lua_tointeger(m_L,index);
        memcpy(result,&i_temp,sizeof(int));
    }
    else if (dataType == DOUBLE)
    {
        double d_temp = lua_tonumber(m_L,index);
        memcpy(result,&d_temp,sizeof(double));
    }
}

void LuaEngine::DeleteGlobalVar(unsigned int dataType,void *field)
{
    if (field == NULL) return;
    switch (dataType)
    {
    case INTEGER:
        delete (int *)field;
        field = NULL;
        break;
    case DOUBLE:
        delete (double *)field;
        field = NULL;
        break;
    case STRING:
        delete [](char *)field;
        field = NULL;
        break;
    case NULLDATA:
        break;
    }
}


void LuaEngine::SetGlobalVar(char *field, void *var, int dataType)
{
    switch (dataType)
    {
    case INTEGER:
        this->PushInt(*((int *)var));
        break;
    case DOUBLE:
        this->PushDouble(*((double *)var));
        break;
    case STRING:
        this->PushString((const char *)var);
        break;
    }
    lua_setglobal(m_L,field);
}

void LuaEngine::GetGlobalTable(char *field, int key, void *result, int dataType)
{
    lua_getglobal(m_L,field);
    this->PushInt(key);
    lua_gettable(m_L,-2);
    this->GetResult(-1,result,dataType);
}



