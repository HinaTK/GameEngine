
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <string>
#include <stdint.h>
#include "export.h"

namespace Function
{
	EXPORT void				WindowsPause();

	EXPORT std::string		WorkDir();

	EXPORT unsigned long	GetThreadID();

	EXPORT bool				ProtocolDecode(const char *buf, unsigned int len);
	EXPORT uint64_t			MarkBit(char mark[]);

	EXPORT void				Info(const char *str, ...);
	EXPORT void				Error(const char *str, ...);
	EXPORT void				CMD(const char *str, ...);	// 进一步优化，支持网络输出
	EXPORT void				CMD();
};

#endif