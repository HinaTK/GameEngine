
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <string>
#include "export.h"

namespace Function
{
	EXPORT void				WindowsPause();

	EXPORT std::string		WorkDir();

	EXPORT unsigned long	GetThreadID();

	EXPORT bool				ProtocolDecode(const char *buf, unsigned int len);

	EXPORT void				Info(char *str, ...);
};

#endif