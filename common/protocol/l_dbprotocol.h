
#ifndef L_DBPROTOCOL_H
#define L_DBPROTOCOL_H

#include "internaltype.h"
#include "../commonvariable.h"
#include "messageheader.h"

namespace IProtocol
{
	struct Test
	{
		Test() :header(MT_TEST){}
		MessageHeader	header;
		char a;
		short b;
		int c;
	};


	struct LDBLogin
	{
		LDBLogin():header(MT_L_DB_LOGIN){}
		MessageHeader	header;
		UInt32			account;
		UInt32			passward;
	};
}

#endif