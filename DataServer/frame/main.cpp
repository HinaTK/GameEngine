
#include <stdio.h>
#include <time.h>
#include "databaseframe.h"

#include "common/commonfunction.h"

int main()
{
	if (!DatabaseFrame::Instance().InitConfig())
	{
		Function::WindowsPause();
		return 0;
	}
	//Log::Instance().Error("writelog");
	DatabaseFrame::Instance().Run();
	Function::WindowsPause();
	return 0;
}
