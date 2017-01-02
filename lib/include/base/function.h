
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

	EXPORT void				Info(const char *str, ...);
	EXPORT void				Error(const char *str, ...);
	EXPORT void				CMD(const char *str, ...);	// 进一步优化，支持网络输出
	EXPORT void				CMD();


};

#define GAME_INFO(Str, ...)\
	Function::Info(__FUNCTION__##":"##Str, __VA_ARGS__);

#define GAME_ERR(Str, ...)\
	Function::Error(__FUNCTION__##":"##Str, __VA_ARGS__);

#endif