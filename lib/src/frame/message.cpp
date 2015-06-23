
#include "frame/message.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/mem.h"

REGISTER_MEMORYPOOL(memorypool, GameMsg, 64);

GameMsg::GameMsg(NetHandle _handle, const char* _data, unsigned int _length)
: call_back_handle(0)
, handle(_handle)
, length(_length)
{
	data = new Mem[length];
	memcpy(data, _data, length);
}

GameMsg::~GameMsg()
{
	delete []data;
}
