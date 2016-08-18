
#ifndef BASE_INTERFACE_H
#define BASE_INTERFACE_H

#include <string>
#include "export.h"

namespace Base
{
	EXPORT void encrypt128(unsigned char *in, unsigned char *out);

	EXPORT void decrypt128(unsigned char *in, unsigned char *out);

	EXPORT std::string MD5Encrypt(std::string &str);
	
	EXPORT std::string MD5Encrypt(const unsigned char *input, size_t length);
}

class GameTime;
namespace Time
{
	EXPORT void Sleep(unsigned int ms);

	EXPORT GameTime * _GameTime();
}



#endif