
#ifndef BASE_EXPORT_H
#define BASE_EXPORT_H

#if (defined _WIN32) || (defined _WIN64)
#define EXPORT _declspec(dllexport)
#else
#define EXPORT
#endif 

#endif
