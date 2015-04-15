
#include "frame/message.h"
#include "lib/include/common/memorypool.h"

REGISTER_MEMORYPOOL(memorypool, GameMsg, 64);

GameMsg::GameMsg(NetHandle _handle, const char* _data, unsigned int _length)
: handle(_handle)
, length(_length)
{
	data = (char *)MemoryVL::Instance().Malloc(length);
	if (data == NULL)
	{
		data = new char[length];
	}
	memcpy(data, _data, length);
}

GameMsg::~GameMsg()
{
	MemoryVL::Instance().Free(data);
}
