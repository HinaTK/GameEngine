
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

void NetMsg::Alloc(NetHandle _handle, unsigned int _length, char *buf)
{
	handle = _handle;
	length = _length;
	if (length > 0)
	{
		data = new char[length];
		memcpy(data, buf, length);
	}
}

void NetMsg::Free()
{
	if (length > 0)
	{
		delete [] data;
	}
}

NetGlobalMsg::NetGlobalMsg(ThreadID _id, NetHandle _handle, unsigned short _length, char *_data)
: id(_id)
, handle(_handle)
, length(_length)
{
	if (length > 0)
	{
		data = (char *)malloc(length);
		memcpy(data, _data, length);
	}
}

NetGlobalMsg::~NetGlobalMsg()
{
	if (length > 0)
	{
		free(data);
	}
}

ThreadMsg::ThreadMsg()
: id(INVALID_THREAD_ID)
, length(0)
, data(NULL)
{

}

ThreadMsg::ThreadMsg(TPT _type, char *_data)
: type(_type)
, id(INVALID_THREAD_ID)
, length(0)
, data(_data)
{

}

ThreadMsg::ThreadMsg(ThreadID _id, TPT _type, char *_data)
: type(_type)
, id(_id)
, length(0)
, data(_data)
{

}

ThreadMsg::ThreadMsg(ThreadID _id, TPT _type, int _length, const char *_data, MsgMemoryManager *memory)
: type(_type)
, id(_id)
, length(_length)
{
	memory->Alloc(&data, _data, _length);
}

ThreadMsg::~ThreadMsg()
{
}

MsgHandler::MsgHandler(MsgCallBack *call_back)
{
	m_bm[BaseMsg::MSG_ACCEPT] 		= new AcceptMsg(call_back);
	m_bm[BaseMsg::MSG_RECV] 		= new RecvMsg(call_back);
	m_bm[BaseMsg::MSG_DISCONNECT] 	= new DisconnectMsg(call_back);
}

MsgHandler::~MsgHandler()
{
	delete m_bm[BaseMsg::MSG_ACCEPT]->m_call_back;
	delete m_bm[BaseMsg::MSG_ACCEPT];
	delete m_bm[BaseMsg::MSG_RECV];
	delete m_bm[BaseMsg::MSG_DISCONNECT];
}