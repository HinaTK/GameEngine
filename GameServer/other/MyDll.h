#ifndef _MY_DLL_H_
#define _MY_DLL_H_

#undef  DLL_SPEC

#if defined (WIN32)
	#if defined (DLL_DEFINE)
		#define DLL_SPEC _declspec(dllexport)
	#else
		#define DLL_SPEC _declspec(dllimport)
	#endif
#else
	#define DLL_SPEC 
#endif

namespace MyDll{
	
	// class in dll
	//class DLL_SPEC CDllClass{	//只需要在windows中添加
	class CDllClass{
	public:
		CDllClass();
		static CDllClass* NewInstance(int x, int y);
		static CDllClass &Instance();
		void Print();

	protected:
		CDllClass(int x,int y);
	protected:
		int m_cx;
		int m_cy;
	};

	// function in dll
	extern "C" int global_mul(int a, int b);
	extern "C" void jiaming();
    extern "C" CDllClass &jjiiaa();
	extern "C" CDllClass *NewInstance();
}

#endif // _MY_DLL_H_

