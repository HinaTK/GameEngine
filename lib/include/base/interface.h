
#ifndef BASE_INTERFACE_H
#define BASE_INTERFACE_H

namespace Base
{
	_declspec(dllexport) void encrypt128(unsigned char *in, unsigned char *out);

	_declspec(dllexport) void decrypt128(unsigned char *in, unsigned char *out);
}

namespace Time
{
	_declspec(dllexport) void *NewTimerManager();

	_declspec(dllexport) void *NewGameTime();
}

#endif