
#include <stdio.h>
#include "export.h"
#include "dll.h"

void Test::Show()
{
	printf("test show ...\n");
}

void Register()
{
	//interface->Set(new DLL);
	printf("fuck fffff\n");
}

void Register(DLL **dll)
{
	*dll = new DLL();
}

void Register(int &a)
{
	a = 123;
}

void Register(Test &test)
{
	test.Show();
}

