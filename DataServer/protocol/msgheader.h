#ifndef MSGHEADER_H
#define MSGHEADER_H

#include "../../common/commonvariable.h"

#pragma pack(push) 
#pragma pack(4)


namespace IProtocol
{
	enum
	{
		MT_INVALID = 0,
	};
	class MessageHeader
	{
	public:
		MessageHeader():msg_type(MT_INVALID){}
		MessageHeader(UInt16 type):msg_type(type), reserved(0){}
		UInt16		msg_type;
		UInt16		reserved;		// 保留位
	};
}

namespace OProtocol
{
	enum
	{
		MT_INVALID = 0,
	};
	class MessageHeader
	{
	public:
		MessageHeader():msg_type(MT_INVALID){}
		MessageHeader(UInt16 type):msg_type(type), reserved(0){}
		UInt16		msg_type;
		UInt16		reserved;		// 保留位
	};
}

#pragma pack(pop)

#endif