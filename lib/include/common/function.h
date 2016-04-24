
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <string>

namespace Function
{
	void			WindowsPause();

	std::string		WorkDir();

	unsigned long	GetThreadID();

	const char		*GetServerName(unsigned int type);

	bool			ProtocolDecode(const char *buf, unsigned int len);
};

#endif