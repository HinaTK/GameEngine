
#include <stdio.h>
#include "accepter.h"
#include "baselistener.h"
#include "netmanager.h"
#include "common/socketdef.h"


Accepter::Accepter(NetManager *manager, int type)
: NetHandler(manager, type)
{
}

