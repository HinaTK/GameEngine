#include <cstdio>

//#if defined (WIN32)
//#define DLL_DEFINE
//#endif

#include "MyDll.h"

namespace MyDll{
	// functions in class
	CDllClass::CDllClass()
	{
		m_cx = 12;
		m_cy = 56;
	} 	

	CDllClass* CDllClass::NewInstance(int x,int y)
	{
		return new CDllClass(x,y);
	}
	
	
	CDllClass &CDllClass::Instance()
	{
		static CDllClass instance;
		return instance;
	}
    CDllClass & jjiiaa()
    {
        static CDllClass instance;
        return instance;
    }

	void CDllClass::Print()
	{
		printf("x=%d,y=%d\n",m_cx,m_cy);
	}

	CDllClass::CDllClass(int x, int y)
		:m_cx(x),m_cy(y)
	{
	}

	// global functions
	int global_mul(int a, int b)
	{
		return a * b;
	}

	void jiaming()
	{
		printf("i am jia ming\n");
	}

}

