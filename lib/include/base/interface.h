
#ifndef BASE_INTERFACE_H
#define BASE_INTERFACE_H

#include <string>

namespace Base
{
	_declspec(dllexport) void encrypt128(unsigned char *in, unsigned char *out);

	_declspec(dllexport) void decrypt128(unsigned char *in, unsigned char *out);

	_declspec(dllexport) std::string MD5Encrypt(std::string &str);
	
	_declspec(dllexport) std::string MD5Encrypt(const unsigned char *input, size_t length);
}

namespace Time
{
	_declspec(dllexport) void *NewTimerManager();

	_declspec(dllexport) void *NewGameTime();

	_declspec(dllexport) void Sleep(unsigned int ms);
}

#endif