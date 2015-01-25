
#ifndef WEBSOKCET_TEST_H
#define WEBSOKCET_TEST_H

#include "frame/websocket/gamewebsocket.h"

namespace WebSocketTest
{
	void Listen()
	{
		GameWebSocket socket;
		socket.Init("192.168.1.102", 9999, 16);
		socket.Listen();
	}
}


#endif