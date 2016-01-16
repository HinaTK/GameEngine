
#include <string>
#include "interface.h"
#include "frame/guimi.h"
#include "common/commonfunction.h"
#include "lib/include/common/mem.h"
#include "lib/include/timemanager/gametime.h"

#define RegisterGlobalFunc(Name)\
	lua_pushcfunction(m_L, Name); \
	lua_setglobal(m_L, #Name);

static NewFrame *frame = &NewFrame::Instance();
static NetManager *net_manager = frame->GetNetManager();
static const int NAME_LEN = 24;

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
	lua_pushboolean(L, net_manager->Send(handle, buf, len));
	Mem::Free(buf);
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
	// todo 由于 area 大小不变，这里之后做优化
	int area_x	= luaL_checkinteger(L, 1);
	int area_y	= luaL_checkinteger(L, 2);
	int map_id	= luaL_checkinteger(L, 3);
	int map_w	= luaL_checkinteger(L, 4);
	int map_h	= luaL_checkinteger(L, 5);
	
	Scene *scene = new Scene(map_id, frame->GetSceneManager());
	scene->Init(map_w, map_h, area_x, area_y);
	lua_pushboolean(L, frame->GetSceneManager()->AddScene(scene));	// ret
	return 1;
}

static int CppEnterScene(lua_State *L)
{
	ObjID obj_id	= luaL_checkunsigned(L, 1);
	MapID map_id	= luaL_checkinteger(L, 2);
	int	x = luaL_checkinteger(L, 3);
	int	y = luaL_checkinteger(L, 4);
	int aoi_w = luaL_checkinteger(L, 5);
	int aoi_h = luaL_checkinteger(L, 6);
// 
// 	lua_pushstring(L, "name");
// 	lua_pushstring(L, "jiaming");
// 	lua_settable(L, -3);

	lua_pushboolean(L, true);	// ret
	lua_pushinteger(L, 123);	// id
	lua_newtable(L);			// leave_other_list
	lua_newtable(L);			// enter_other_list
	lua_newtable(L);			// other_enter_list
	return 5;
}

static int CppLeaveScene(lua_State *L)
{
	lua_pop(L, 1);

	lua_pushboolean(L, true);	// ret
	lua_pushinteger(L, 123);	// id
	lua_newtable(L);			// leave_other_list
	return 3;
}

static int CppStartMove(lua_State *L)
{
	lua_pop(L, 1);

	lua_pushboolean(L, true);	// ret
	lua_pushinteger(L, 123);	// id
	lua_newtable(L);			// notify_list
	return 3;
}

static int CppStopMove(lua_State *L)
{
	lua_pop(L, 3);

	lua_pushboolean(L, true);	// ret
	lua_pushinteger(L, 123);	// id
	lua_newtable(L);			// notify_list
	lua_newtable(L);			// leave_other_list
	lua_newtable(L);			// enter_other_list
	lua_newtable(L);			// other_leave_list
	lua_newtable(L);			// other_enter_list

	return 7;
}

static int CppSynPosition(lua_State *L)
{
	lua_pop(L, 3);

	lua_pushboolean(L, true);	// ret
	lua_pushinteger(L, 123);	// id
	lua_newtable(L);			// notify_list
	lua_newtable(L);			// leave_other_list
	lua_newtable(L);			// enter_other_list
	lua_newtable(L);			// other_leave_list
	lua_newtable(L);			// other_enter_list

	return 7;
}

static int CppCreateObj(lua_State *L)
{
	lua_pushinteger(L, frame->GetSceneManager()->CreateRole());
	return 1;
}

static int CppDestroyObj(lua_State *L)
{
	lua_pop(L, 1);
	return 0;
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
	RegisterGlobalFunc(CppTest);
	RegisterGlobalFunc(CppConnect);
	RegisterGlobalFunc(CppDisconnect);
	RegisterGlobalFunc(CppListen);
	RegisterGlobalFunc(CppListenXXX);
	RegisterGlobalFunc(CppSend);
	RegisterGlobalFunc(CppPrint);
	RegisterGlobalFunc(CppDecGsNetid);
	RegisterGlobalFunc(CppEncGsNetid);
	RegisterGlobalFunc(CppTime);
	RegisterGlobalFunc(CppInitScene);
	RegisterGlobalFunc(CppEnterScene);
	RegisterGlobalFunc(CppLeaveScene);
	RegisterGlobalFunc(CppStartMove);
	RegisterGlobalFunc(CppStopMove);
	RegisterGlobalFunc(CppSynPosition);
	RegisterGlobalFunc(CppCreateObj);
	RegisterGlobalFunc(CppDestroyObj);
	RegisterGlobalFunc(CppNextDayInterval);
	RegisterGlobalFunc(CppCreateTimerSecond);

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

void Interface::OnRecv(NetHandle netid, unsigned int length, const char *data)
{
	char name[NAME_LEN] = { 0 };
	memcpy(name, data, NAME_LEN);
	name[NAME_LEN - 1] = 0;

	lua_getglobal(m_L, "OnRecv");
	lua_pushinteger(m_L, netid);
	lua_pushstring(m_L, name);
	lua_pushlstring(m_L, data + NAME_LEN, length - NAME_LEN);
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

void Interface::OnInnerRecv(NetHandle netid, unsigned int length, const char *data)
{
	char name[NAME_LEN] = { 0 };
	memcpy(name, data, NAME_LEN);
	name[NAME_LEN - 1] = 0;

	lua_getglobal(m_L, "OnInnerRecv");
	lua_pushinteger(m_L, netid);
	lua_pushstring(m_L, name);
	lua_pushlstring(m_L, data + NAME_LEN, length - NAME_LEN);
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

void Interface::OnXXXRecv(NetHandle netid, unsigned int length, const char *data)
{
	int begin = sizeof(int);
	char name[NAME_LEN] = { 0 };
	memcpy(name, data + begin, NAME_LEN);
	name[NAME_LEN - 1] = 0;
	begin += NAME_LEN;

	lua_getglobal(m_L, "OnXXXRecv");
	lua_pushinteger(m_L, netid);
	lua_pushinteger(m_L, *(int *)data);
	lua_pushstring(m_L, name);
	lua_pushlstring(m_L, data + begin, length - begin);
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

