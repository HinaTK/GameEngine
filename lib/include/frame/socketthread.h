
#ifndef SOCKET_THREAD_H
#define SOCKET_THREAD_H

#if (defined _WIN32) || (defined _WIN64)
#include "threadselect.h"
#endif // WIN32
#ifdef __unix
#include "threadepoll.h"
#endif // __unix



#endif