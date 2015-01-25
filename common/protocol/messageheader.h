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
		MessageHeader(unsigned short type):msg_type(type), msg_len(0){}
		unsigned int	msg_type;
		unsigned int	msg_len;		// 消息长度
	};
	
	static const int LENGTH = sizeof(MessageHeader);
}

namespace EProtocol
{
	enum
	{
		MT_INVALID = 0,
	};
	class MessageHeader
	{
	public:
		MessageHeader():msg_type(MT_INVALID){}
		MessageHeader(unsigned short type):msg_type(type), msg_len(0){}
		unsigned short	msg_type;
		unsigned short	msg_len;		// 消息长度
	};

	static const int LENGTH = sizeof(MessageHeader);
}

#pragma pack(pop)

#endif