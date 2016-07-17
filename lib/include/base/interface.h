
#ifndef BASE_INTERFACE_H
#define BASE_INTERFACE_H

#include <string>

#ifdef WIN32
#define EXPORT _declspec(dllexport)
#else
#define EXPORT 
#endif // WIN32

namespace Base
{
	EXPORT void encrypt128(unsigned char *in, unsigned char *out);

	EXPORT void decrypt128(unsigned char *in, unsigned char *out);

	EXPORT std::string MD5Encrypt(std::string &str);
	
	EXPORT std::string MD5Encrypt(const unsigned char *input, size_t length);
}

class GameTime;
class TimerManager;
namespace Time
{
	EXPORT TimerManager *_TimerManager();

	EXPORT void Sleep(unsigned int ms);

	EXPORT GameTime * _GameTime();
}

#endif