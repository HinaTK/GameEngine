
#include <string.h>
#include "script/luaengine.h"


LuaEngine::LuaEngine()
{
}


lua_State* LuaEngine::InitLuaEnv()
{
//  LuaEnv = lua_open(); //旧版本用法
    m_luaEnv = luaL_newstate();
    return m_luaEnv;
}


bool LuaEngine::LoadLuaFile(std::string fileName)
{
    if (m_luafile != fileName)
    {
        m_luaEnv = luaL_newstate();
        if (luaL_loadfile(m_luaEnv, fileName.c_str()) || lua_pcall(m_luaEnv, 0, 0, 0))
        {
            printf("%s\n",lua_tostring(m_luaEnv, -1));
            return false;
        }
        m_luafile = fileName;
    }

    return true;
}



void LuaEngine::PushString(std::string str)
{
    lua_pushstring(m_luaEnv,str.c_str());
}


void LuaEngine::PushInt(int data)
{
    lua_pushinteger(m_luaEnv,data);
}

void LuaEngine::PushDouble(double data)
{
    lua_pushnumber(m_luaEnv,data);
}

// 获取全局函数.
bool LuaEngine::GetGlobalProc(const std::string& procName, int arg, int result)
{
    lua_getglobal(m_luaEnv, procName.c_str());
    if (!lua_isfunction(m_luaEnv, 1))
    {
        return false;
    }

    lua_tocfunction(m_luaEnv, 1);
    lua_pcall(m_luaEnv,arg,result,0);   //arg:传入参数的个数   //result:得到返回值的个数
    return true;
}



void LuaEngine::GetGlobalVar(char *field, void *result, int type)
{
    lua_pcall(m_luaEnv,0,0,0);

    lua_getglobal(m_luaEnv,field);
    if (type == STRING)
    {
        memcpy(result,lua_tostring(m_luaEnv,-1),strlen(lua_tostring(m_luaEnv,-1)));
    }
    else if (type == INTEGER)
    {
        int i_temp = lua_tointeger(m_luaEnv,-1);
        memcpy(result,&i_temp,sizeof(int));
    }
    else if (type == DOUBLE)
    {
        double d_temp = lua_tonumber(m_luaEnv,-1);
        memcpy(result,&d_temp,sizeof(double));
    }

}

// 获取全局变量
//可用于读取配置
//lua_isstring 是否能转换成字符串

int LuaEngine::GetGlobalVar( char *field, void **result/*,int type = NULLDATA*/ )
{
	lua_pcall(m_luaEnv,0,0,0);

	lua_getglobal(m_luaEnv,field);
	int i_temp = 0;
	double d_temp = 0.0;
	if (lua_isnumber(m_luaEnv,-1))
	{
		i_temp=lua_tointeger(m_luaEnv,-1);
		d_temp=lua_tonumber(m_luaEnv,-1);
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
	else if (lua_isstring(m_luaEnv,-1))
	{
		unsigned int lenght = 0;
		lenght = strlen(lua_tostring(m_luaEnv,-1));
		*result = new char[lenght];
		memcpy(*result,lua_tostring(m_luaEnv,-1),lenght);
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
    if (lua_isnumber(m_luaEnv,index))
    {
        i_temp=lua_tointeger(m_luaEnv,index);
        d_temp=lua_tonumber(m_luaEnv,index);
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
    else if (lua_isstring(m_luaEnv,index))
    {
        unsigned int lenght = 0;
        lenght = strlen(lua_tostring(m_luaEnv,index));
        *result = new char[lenght];
        memcpy(*result,lua_tostring(m_luaEnv,index),lenght);
        ((char*)*result)[lenght] = '\0';
        return STRING;
    }
    return NULLDATA;
}


void LuaEngine::GetResult(int index, void *result, int dataType)
{
    if (dataType == STRING)
    {
        memcpy(result,lua_tostring(m_luaEnv,index),strlen(lua_tostring(m_luaEnv,index)));
    }
    else if (dataType == INTEGER)
    {
        int i_temp = lua_tointeger(m_luaEnv,index);
        memcpy(result,&i_temp,sizeof(int));
    }
    else if (dataType == DOUBLE)
    {
        double d_temp = lua_tonumber(m_luaEnv,index);
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
    lua_setglobal(m_luaEnv,field);
}

void LuaEngine::GetGlobalTable(char *field, int key, void *result, int dataType)
{
    lua_getglobal(m_luaEnv,field);
    this->PushInt(key);
    lua_gettable(m_luaEnv,-2);
    this->GetResult(-1,result,dataType);
}



