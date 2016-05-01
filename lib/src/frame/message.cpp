
#include "frame/message.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/memoryvl.h"
#include "lib/include/common/mem.h"

REGISTER_SAFE_MEMORYPOOL(safememorypool, GameMsg, 64);
REGISTER_SAFE_MEMORYPOOL(safememorypool, ThreadMsg, 64);

GameMsg::GameMsg(unsigned short _msg_index, unsigned short _msg_type, NetHandle _handle, char* _data, unsigned int _length)
: msg_index(_msg_index)
, msg_type(_msg_type)
, handle(_handle)
, length(_length)
, data(_data)
{
	
}

GameMsg::~GameMsg()
{
	
}

GameMsgManager::GameMsgManager()
: memory(Mem::NewMemoryVL())
{

}

GameMsgManager::~GameMsgManager()
{
	if (memory != NULL)
	{
		delete memory;
		memory = NULL;
	}
}

GameMsg * GameMsgManager::Alloc(unsigned short msg_index, unsigned short msg_type, NetHandle handle, const char* data, unsigned int length)
{
	char *new_data = NULL;
	if (length > 0)
	{
		new_data = (char *)memory->Alloc(length);
		memcpy(new_data, data, length);
	}
	return new GameMsg(msg_index, msg_type, handle, new_data, length);
}

void GameMsgManager::Free(GameMsg *msg)
{
	if (msg->length > 0)
	{
		memory->Free(msg->data);
	}
	delete msg;
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

