
#ifndef BASE_EXPORT_H
#define BASE_EXPORT_H

#ifdef WIN32
#define EXPORT _declspec(dllexport)
#else
#define EXPORT 
#endif // WIN32

#endif