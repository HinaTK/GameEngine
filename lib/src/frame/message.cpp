
#include "frame/message.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/memoryvl.h"
#include "lib/include/common/mem.h"


GameMsg::GameMsg()
: msg_index(0)
, msg_type(0)
, handle(0)
, length(0)
, data(NULL)
{

}

GameMsg::GameMsg(unsigned short _msg_index, GameMsgType _msg_type, NetHandle _handle, unsigned int _length)
: msg_index(_msg_index)
, msg_type(_msg_type)
, handle(_handle)
, length(_length)
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

void GameMsgManager::Alloc(char **buf, const char *data, unsigned int length)
{
	if (length > 0)
	{
		*buf = (char *)memory->Alloc(length);
		memcpy(*buf, data, length);
	}
}

char * GameMsgManager::Alloc(unsigned int length)
{
	if (length > 0)
	{
		return (char *)memory->Alloc(length);
	}
	return NULL;
}

void GameMsgManager::Free(GameMsg &msg)
{
	if (msg.length > 0)
	{
		memory->Free(msg.data);
	}
}

ThreadMsg::ThreadMsg()
: length(0)
{

}

ThreadMsg::ThreadMsg(short _type, ThreadID _id, int _length, const char *_data)
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
}

void ThreadMsg::Release()
{
	if (length > 0)
	{
		length = 0;
		Mem::TFree(data);
	}
}

