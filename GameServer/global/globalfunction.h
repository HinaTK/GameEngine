#ifndef GLOBALFUNCTION_H
#define GLOBALFUNCTION_H

#ifdef __LINUX__
#include <unistd.h>
#endif

namespace GLOBALFUNCTION
{
    void		GameInit();

//    void		GetProgramName(ProgramName name);

	void		PrintWorkDir();		// �������Ŀ¼�����ڵ���

}

#endif // GLOBALFUNCTION_H
