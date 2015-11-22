
#ifndef L_DBPROTOCOL_H
#define L_DBPROTOCOL_H

#include "internaltype.h"
#include "../commonvariable.h"
#include "messageheader.h"

namespace IProtocol
{
	struct Test
	{
		Test() :header(0){}
		MessageHeader	header;
		char a;
		short b;
		int c;
	};


	struct LDBLogin
	{
		LDBLogin():header(0){}
		MessageHeader	header;
		UInt32			account;
		UInt32			passward;
	};
}

#endif