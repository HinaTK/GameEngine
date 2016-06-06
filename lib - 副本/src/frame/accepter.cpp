
#include <stdio.h>
#include "accepter.h"
#include "baselistener.h"
#include "netmanager.h"
#include "common/socketdef.h"


Accepter::Accepter(SocketThread *t, int type)
: NetHandler(t, type)
{
}

