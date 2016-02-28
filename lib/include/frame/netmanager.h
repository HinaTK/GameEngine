
#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#ifdef WIN32
#include "net_win.h"
#endif

#ifdef __unix
#include "net_unix.h"
#endif

#endif
