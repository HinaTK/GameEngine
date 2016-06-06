
#ifndef SOCKET_THREAD_H
#define SOCKET_THREAD_H

#ifdef WIN32
#include "threadselect.h"
#endif // WIN32
#ifdef __unix
#include "threadepoll.h"
#endif // __unix



#endif