
#ifdef WIN32
#include <direct.h>
#endif // Win32

#include <stdio.h>
#include "globalfunction.h"
#include "globalvariable.h"


namespace GLOBALFUNCTION
{
//     void GetProgramName(ProgramName name)
//     {
// #ifdef __linucx
//         static  char filename[PROGRAMNAMELEN]={'\0'};
//         if (filename[0] != '\0')
//         {
//             memcpy(name, filename, PROGRAMNAMELEN * sizeof(char));
//         }
//         char sysfile[15] = "/proc/self/exe";
// 
//         if ( -1 == readlink( sysfile,filename,PROGRAMNAMELEN ) )
//         {
//            memcpy(filename,"GameServer",sizeof("GameServer"));
//         }
// 		memcpy(name, filename, PROGRAMNAMELEN * sizeof(char));
// #else
//         memcpy(name, "GameServer", sizeof("GameServer"));
// #endif
//         
//     }

	void PrintWorkDir()
	{
#ifdef WIN32
		char path[512] = {0};
		_getcwd(path, 512);
		printf("当前工作目录:\n%s\n", path);
#endif
	}

	


}
