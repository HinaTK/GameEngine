
#include <stdio.h>
#include <time.h>
#include "dataframe.h"

#include "common/commonfunction.h"

int main()
{
	if (!NewFrame::Instance().InitConfig())
	{
		Function::WindowsPause();
		return 0;
	}
	//Log::Instance().Error("writelog");
	NewFrame::Instance().Run();
	Function::WindowsPause();
	return 0;
}
