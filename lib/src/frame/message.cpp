
#include "frame/message.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/mem.h"

REGISTER_MEMORYPOOL(memorypool, GameMsg, 64);

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
