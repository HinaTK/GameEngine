
#ifndef ROUTER_H
#define ROUTER_H

#include "common/socketdef.h"

namespace Router
{
	void RegisterServer(NetHandle handle, int len, char *data);
}

#endif