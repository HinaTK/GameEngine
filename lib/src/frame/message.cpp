
#include "frame/message.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/mem.h"

REGISTER_SAFE_MEMORYPOOL(safememorypool, GameMsg, 64);
REGISTER_SAFE_MEMORYPOOL(safememorypool, ThreadMsg, 64);
REGISTER_SAFE_MEMORYPOOL(safememorypool, GlobalMsg, 64);

GameMsg::GameMsg(unsigned short _msg_index, unsigned short _msg_type, NetHandle _handle, const char* _data, unsigned int _length)
: msg_index(_msg_index)
, msg_type(_msg_type)
, handle(_handle)
, length(_length)
{
	data = Mem::Alloc(length);
	memcpy(data, _data, length);
}

GameMsg::~GameMsg()
{
	Mem::Free(data);
}

ThreadMsg::ThreadMsg(int _length, const char *_data)
: length(_length)
{
	data = Mem::TAlloc(length);
	memcpy(data, _data, length);
}

ThreadMsg::~ThreadMsg()
{
	Mem::TFree(data);
}

GlobalMsg::GlobalMsg(unsigned char _type, ThreadMsg *_msg)
: type(_type)
, msg(_msg)
{

}

GlobalMsg::~GlobalMsg()
{

}
