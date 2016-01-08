
#include <stdio.h>
#include "guimi.h"
#include "common/commonfunction.h"

int main()
{
	NewFrame::Instance().Init();
	Function::WindowsPause();
	
	return 0;
}