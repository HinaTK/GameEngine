#include "test.h"

void Test::Init()
{
	a = 1;
	b = 2;
	c = 3;
	d = 4;
	e = (char *)malloc(16 * sizeof(char));
	memcpy(e, "һͷ��", sizeof("һͷ��"));
}

void Test::Show()
{
	printf("%d\n",a);
	printf("%f\n",b);
	printf("%c\n",c);
	printf("%f\n",d);
	printf("%s\n",e);
}


