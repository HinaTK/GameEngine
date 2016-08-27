
#include "message.h"
#include "lib/include/thread/threadclass.h"
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
: handle(0)
, length(0)
, data(NULL)
{

}

NetMsg::NetMsg(NetHandle _handle, unsigned int _length)
: handle(_handle)
, length(_length)
{

}

NetMsg::NetMsg(NetHandle _handle, char *_data, unsigned int _length)
: handle(_handle)
, data(_data)
, length(_length)
{

}

NetMsg::~NetMsg()
{
	
}


ThreadMsg::ThreadMsg()
: length(0)
, data(NULL)
{

}

ThreadMsg::ThreadMsg(short _type, ThreadID _id, ThreadClass *tc)
: type(_type)
, id(_id)
, length(0)
, data((char *)tc)
{

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
