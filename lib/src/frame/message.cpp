
#include "frame/message.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/mem.h"

REGISTER_SAFE_MEMORYPOOL(safememorypool, GameMsg, 64);
REGISTER_SAFE_MEMORYPOOL(safememorypool, ThreadMsg, 64);

GameMsg::GameMsg(unsigned short _msg_index, unsigned short _msg_type, NetHandle _handle, const char* _data, unsigned int _length)
: msg_index(_msg_index)
, msg_type(_msg_type)
, handle(_handle)
, length(_length)
{
	if (length > 0)
	{
		data = Mem::Alloc(length);
		memcpy(data, _data, length);
	}
}

GameMsg::~GameMsg()
{
	if (length > 0)
	{
		Mem::Free(data);
	}
}

ThreadMsg::ThreadMsg(short _type, int _id, int _length, const char *_data)
: type(_type)
, id(_id)
, length(_length)
{
	if (length > 0)
	{
		data = Mem::TAlloc(length);
		memcpy(data, _data, length);
	}
}

ThreadMsg::~ThreadMsg()
{
	if (length > 0)
	{
		Mem::TFree(data);
	}
}