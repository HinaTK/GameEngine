#ifndef COMMONFUNCTION_H
#define COMMONFUNCTION_H

#include "systemdef.h"
#ifdef __unix
	
#endif



#include <string>

namespace Function
{
	void			WindowsPause();

	std::string		WorkDir();

	unsigned long	GetThreadID();

	const char		*GetServerName(unsigned int type);
};

#endif