
#include <string>
#include "interface.h"
#include "frame/guimi.h"
#include "common/commonfunction.h"
#include "lib/include/common/mem.h"
#include "lib/include/timemanager/gametime.h"

static NetManager *net_manager = NewFrame::Instance().GetNetManager();

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

static int CppListen(lua_State *L)
{
	const char *flag = luaL_checkstring(L, 1);
	int port = luaL_checkinteger(L, 2);
	int back_log = luaL_checkinteger(L, 3);

	bool ret = false;
	if (strcmp(flag, "inner") == 0)
	{
		ret = net_manager->InitServer("127.0.0.1", port, back_log, new Accepter(net_manager), NewFrame::Instance().GetInterface()->GetInnerCallBack());
	}
	else
	{
		ret = net_manager->InitServer("0.0.0.0", port, back_log, new Accepter(net_manager), NewFrame::Instance().GetInterface()->GetOuterCallBack());
	}
	lua_pushboolean(L, ret);
	return 1;
}

static int CppListenXXX(lua_State *L)
{
	const char *flag = luaL_checkstring(L, 1);
	int port = luaL_checkinteger(L, 2);
	int back_log = luaL_checkinteger(L, 3);

	bool ret = net_manager->InitServer("0.0.0.0", port, back_log, new Accepter(net_manager), NewFrame::Instance().GetInterface()->GetXXXCallBack());
	lua_pushboolean(L, ret);
	return 1;
}

static int CppConnect(lua_State *L)
{
	const char *flag = luaL_checkstring(L, 1);
	const char *host = luaL_checkstring(L, 2);
	int port = luaL_checkinteger(L, 3);
	NetHandle handle = INVALID_NET_HANDLE;
	if (strcmp(flag, "inner") == 0)
	{
		handle = net_manager->ConnectServer(host, port, new BaseListener(net_manager), NewFrame::Instance().GetInterface()->GetInnerCallBack());
	}
	else
	{
		handle = net_manager->ConnectServer(host, port, new BaseListener(net_manager), NewFrame::Instance().GetInterface()->GetOuterCallBack());
	}
	
	if (handle == INVALID_NET_HANDLE)
	{
		lua_pushboolean(L, false);
	}
	else
	{
		lua_pushinteger(L, handle);
	}
	return 1;
}

static int CppDisconnect(lua_State *L)
{
	return 1;
}

static int CppSend(lua_State *L) 
{
	size_t nsz = 0;
	size_t dsz = 0;
	const char *flag	= luaL_checkstring(L, 1);
	NetHandle  handle	= luaL_checkinteger(L, 2);
	const char *name	= luaL_checklstring(L, 3, &nsz);
	const char *data	= luaL_checklstring(L, 4, &dsz);

	unsigned int len = (unsigned int)(24 + dsz);
	char *buf = Mem::Alloc(len);
	memset(buf, 0, len);
	char *temp = buf;
	memcpy(temp, name, nsz);
	temp += 24;
	memcpy(temp, data, dsz);
	char test[256] = { 0 };
	memcpy(test, buf, len);
	lua_pushboolean(L, net_manager->Send(handle, buf, len));
	Mem::Free(buf);

// 	if (strcmp(flag, "gate") == 0)
// 	{
// 		unsigned int len = (int)(4 + 24 + dsz);
// 		char *buf = Mem::Alloc(len);
// 		*(unsigned int *)buf = len;
// 		char *temp = buf + 4;
// 		memcpy(temp, name, nsz);
// 		temp += 24;
// 		memcpy(temp, data, dsz);
// 		lua_pushboolean(L, net_manager->Send(handle, buf, len));
// 		Mem::Free(buf);
// 	}
// 	else
// 	{
// 		unsigned int len = (int)(nsz + dsz + sizeof(size_t)* 2);
// 		char *buf = Mem::Alloc(len);
// 		*(size_t *)buf = nsz;
// 		char *temp = buf + sizeof(size_t);
// 		memcpy(temp, name, nsz);
// 		temp += nsz;
// 		*(size_t *)temp = dsz;
// 		temp += sizeof(size_t);
// 		memcpy(temp, data, dsz);
// 		lua_pushboolean(L, net_manager->Send(handle, buf, len));
// 		Mem::Free(buf);
// 	}
// 	
	

// 	if (strcmp(flag, "inner") == 0)
// 	{
// 		size_t len = nsz + dsz + sizeof(size_t)* 2;
// 		char *buf = Mem::Alloc(len);
// 		*(size_t *)buf = nsz;
// 		char *temp = buf + sizeof(size_t);
// 		memcpy(temp, name, nsz);
// 		temp += nsz;
// 		*(size_t *)temp = dsz;
// 		temp += sizeof(size_t);
// 		memcpy(temp, data, dsz);
// 		net_manager->Send(handle, buf, len);
// 		Mem::Free(buf);
// 	}
// 	else
// 	{
// 		net_manager->Send(handle, data, dsz);
// 	}
	return 1;
}

static int CppPrint(lua_State *L)
{
	const char *flag = luaL_checkstring(L, 1);
	const char *msg = luaL_checkstring(L, 2);
	printf("%s %s\n", flag, msg);
	return 0;
}

static int CppDecGsNetid(lua_State *L)
{
	NetHandle handle = luaL_checkinteger(L, 1);

	NetHandle ihandle = handle >> 24;
	NetHandle ohandle = (handle << 8) >> 8;

	lua_pushinteger(L, ihandle);
	lua_pushinteger(L, ohandle);
	return 2;
}

static int CppEncGsNetid(lua_State *L)
{
	NetHandle ihandle = luaL_checkinteger(L, 1);
	NetHandle ohandle = luaL_checkinteger(L, 2);

	NetHandle handle = ihandle << 24;
	handle = handle | ((ohandle << 8) >> 8);
	lua_pushinteger(L, handle);
	return 1;
}

static int CppTime(lua_State *L)
{
	lua_pushunsigned(L, (unsigned int)GameTime::Instance().Time());
	return 1;
}

static int CppInitScene(lua_State *L)
{
	return 1;
}

static int CppEnterScene(lua_State *L)
{
	lua_newtable(L);			// other_enter_list
// 
// 	lua_pushstring(L, "name");
// 	lua_pushstring(L, "jiaming");
// 	lua_settable(L, -3);

	lua_newtable(L);			// enter_other_list
	lua_newtable(L);			// leave_other_list
	lua_pushinteger(L, 123);	// id
	lua_pushboolean(L, true);	// ret
	return 5;
}

static int CppLeaveScene(lua_State *L)
{
	lua_newtable(L);			// leave_other_list
	lua_pushinteger(L, 123);	// id
	lua_pushboolean(L, true);	// ret
	return 3;
}

static int CppCreateObj(lua_State *L)
{
	return 1;
}

static int CppNextDayInterval(lua_State *L)
{
	return 1;
}

static int CppCreateTimerSecond(lua_State *L)
{
	return 1;
}

static int CppTest(lua_State *L)
{
	size_t fsz = 0;
	const char *flag = luaL_checklstring(L, 1, &fsz);
	char test[256] = { 0 };
	memcpy(test, flag, fsz);
	lua_pushlstring(L, flag, fsz);
	return 1;
}


// static const struct luaL_Reg lib[] = {
// 	{ "CppSend", CppSend },
// 	{ NULL, NULL }
// };

Interface::Interface()
: m_o_call_back(this)
, m_i_call_back(this)
, m_x_call_back(this)
{
	m_L = luaL_newstate();
	luaL_openlibs(m_L);
}

Interface::~Interface()
{
	lua_close(m_L);
}

bool Interface::LoadFile(const char *file)
{
	lua_pushcfunction(m_L, CppTest);
	lua_setglobal(m_L, "CppTest");

	lua_pushcfunction(m_L, CppConnect);
	lua_setglobal(m_L, "CppConnect");

	lua_pushcfunction(m_L, CppDisconnect);
	lua_setglobal(m_L, "CppDisconnect");

	lua_pushcfunction(m_L, CppListen);
	lua_setglobal(m_L, "CppListen");

	lua_pushcfunction(m_L, CppListenXXX);
	lua_setglobal(m_L, "CppListenXXX");

	lua_pushcfunction(m_L, CppSend);
	lua_setglobal(m_L, "CppSend");

	lua_pushcfunction(m_L, CppPrint);
	lua_setglobal(m_L, "CppPrint");

	lua_pushcfunction(m_L, CppDecGsNetid);
	lua_setglobal(m_L, "CppDecGsNetid");

	lua_pushcfunction(m_L, CppEncGsNetid);
	lua_setglobal(m_L, "CppEncGsNetid");

	lua_pushcfunction(m_L, CppTime);
	lua_setglobal(m_L, "CppTime");

	lua_pushcfunction(m_L, CppInitScene);
	lua_setglobal(m_L, "CppInitScene");

	lua_pushcfunction(m_L, CppEnterScene);
	lua_setglobal(m_L, "CppEnterScene");
	
	lua_pushcfunction(m_L, CppLeaveScene);
	lua_setglobal(m_L, "CppLeaveScene");

	lua_pushcfunction(m_L, CppCreateObj);
	lua_setglobal(m_L, "CppCreateObj");

	lua_pushcfunction(m_L, CppNextDayInterval);
	lua_setglobal(m_L, "CppNextDayInterval");

	lua_pushcfunction(m_L, CppCreateTimerSecond);
	lua_setglobal(m_L, "CppCreateTimerSecond");

	std::string path = Function::WorkDir() + file;
	if (luaL_loadfile(m_L, path.c_str()) || lua_pcall(m_L, 0, 0, 0))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return false;
	}
	return true;
}

void Interface::OnInit()
{
	lua_pushcfunction(m_L, traceback);
	lua_getglobal(m_L, "OnInit");

	if (lua_pcall(m_L, 0, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
	
}

void Interface::OnUpdate(int interval, unsigned int now)
{
	lua_getglobal(m_L, "OnUpdate");
	lua_pushinteger(m_L, interval);
	lua_pushinteger(m_L, now);
	if (lua_pcall(m_L, 2, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

void Interface::OnAccept(NetHandle netid, const char *ip)
{
	lua_getglobal(m_L, "OnAccept");
	lua_pushinteger(m_L, netid);
	lua_pushstring(m_L, ip);
	if (lua_pcall(m_L, 2, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

void Interface::OnRecv(NetHandle netid, const char *name, size_t dsz, const char *data)
{
	char test[256] = { 0 };
	memcpy(test, data, dsz);
	lua_getglobal(m_L, "OnRecv");
	lua_pushinteger(m_L, netid);
	lua_pushstring(m_L, name);
	lua_pushlstring(m_L, data, dsz);
	if (lua_pcall(m_L, 3, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

void Interface::OnDisconnect(NetHandle netid)
{
	lua_getglobal(m_L, "OnDisconnect");
	lua_pushinteger(m_L, netid);
	if (lua_pcall(m_L, 1, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

void Interface::OnInnerAccept(NetHandle netid, const char *ip)
{
	lua_getglobal(m_L, "OnInnerAccept");
	lua_pushinteger(m_L, netid);
	lua_pushstring(m_L, ip);
	if (lua_pcall(m_L, 2, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

void Interface::OnInnerRecv(NetHandle netid, const char *name, size_t dsz, const char *data)
{
	lua_getglobal(m_L, "OnInnerRecv");
	lua_pushinteger(m_L, netid);
	lua_pushstring(m_L, name);
	lua_pushlstring(m_L, data, dsz);
	if (lua_pcall(m_L, 3, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

void Interface::OnInnerDisconnect(NetHandle netid)
{
	lua_getglobal(m_L, "OnInnerDisconnect");
	lua_pushinteger(m_L, netid);
	if (lua_pcall(m_L, 1, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

void Interface::OnXXXAccept(NetHandle netid, const char *ip)
{
	lua_getglobal(m_L, "OnXXXAccept");
	lua_pushinteger(m_L, netid);
	lua_pushstring(m_L, ip);
	if (lua_pcall(m_L, 2, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

void Interface::OnXXXRecv(NetHandle netid, int server_id, const char *name, size_t dsz, const char *data)
{
	lua_getglobal(m_L, "OnXXXRecv");
	lua_pushinteger(m_L, netid);
	lua_pushinteger(m_L, server_id);
	lua_pushstring(m_L, name);
	lua_pushlstring(m_L, data, dsz);
	if (lua_pcall(m_L, 4, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

void Interface::OnXXXDisconnect(NetHandle netid)
{
	lua_getglobal(m_L, "OnXXXDisconnect");
	lua_pushinteger(m_L, netid);
	if (lua_pcall(m_L, 1, 0, 1))
	{
		printf("%s\n", lua_tostring(m_L, -1));
		return;
	}
}

