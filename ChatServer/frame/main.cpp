
#include "libcommon.h"

int main()
{
	char abc[1024];
	memcpy(abc, MD5("xianjiaming").toString().c_str(), MD5("xianjiaming").toString().length());
	printf("\n");
	
	return 0;
}