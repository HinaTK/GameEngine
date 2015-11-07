
#include "frame/message.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/mem.h"

REGISTER_MEMORYPOOL(memorypool, GameMsg, 64);

GameMsg::GameMsg(NetHandle _handle, int _call_back_handle, const char* _data, unsigned int _length)
: call_back_handle(_call_back_handle)
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
