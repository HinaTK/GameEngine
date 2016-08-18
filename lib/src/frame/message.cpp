
#include "frame/message.h"
#include "lib/include/common/memorypool.h"
#include "lib/include/common/memoryvl.h"
#include "lib/include/common/mem.h"

MsgMemoryManager::MsgMemoryManager()
: memory(Mem::NewMemoryVL())
{

}

MsgMemoryManager::~MsgMemoryManager()
{
	if (memory != NULL)
	{
		delete memory;
		memory = NULL;
	}
}

void MsgMemoryManager::Alloc(char **buf, const char *data, unsigned int length)
{
	if (length > 0)
	{
		*buf = (char *)memory->Alloc(length);
		memcpy(*buf, data, length);
	}
}

char * MsgMemoryManager::Alloc(unsigned int length)
{
	if (length > 0)
	{
		return (char *)memory->Alloc(length);
	}
	return NULL;
}

NetMsg::NetMsg()
: msg_index(0)
, msg_type(0)
, handle(0)
, length(0)
, data(NULL)
{

}

NetMsg::NetMsg(unsigned short _msg_index, NetMsgType _msg_type, NetHandle _handle, unsigned int _length)
: msg_index(_msg_index)
, msg_type(_msg_type)
, handle(_handle)
, length(_length)
{

}

NetMsg::~NetMsg()
{
	
}


ThreadMsg::ThreadMsg()
: length(0)
{

}

template<typename T>
ThreadMsg::ThreadMsg(short _type, ThreadID _id, T &_data, MsgMemoryManager *memory)
: type(_type)
, id(_id)
, length(_length)
{
	data = memory->Alloc(sizeof(T));
	*(T *)(data) = _data;
}


ThreadMsg::ThreadMsg(short _type, ThreadID _id, int _length, const char *_data, MsgMemoryManager *memory)
: type(_type)
, id(_id)
, length(_length)
{
	memory->Alloc(&data, _data, _length);
}

ThreadMsg::~ThreadMsg()
{
}
