
#include <stdio.h>
#include "guimi.h"
#include "common/commonfunction.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("lack argument ...\n");
		return 0;
	}

	NewFrame::Instance().Init(argv[1]);
	NewFrame::Instance().Run();
	Function::WindowsPause();
	
	return 0;
}