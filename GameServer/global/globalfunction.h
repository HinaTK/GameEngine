#ifndef GLOBALFUNCTION_H
#define GLOBALFUNCTION_H

#ifdef __LINUX__
#include <unistd.h>
#endif

namespace GLOBALFUNCTION
{
    void		GameInit();

//    void		GetProgramName(ProgramName name);

	void		PrintWorkDir();		// 输出工作目录，用于调试

}

#endif // GLOBALFUNCTION_H
