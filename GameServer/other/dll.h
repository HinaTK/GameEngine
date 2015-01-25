#ifndef DLL_H
#define DLL_H

#ifdef __LINUX__

#include <dlfcn.h>
#include <map>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

//一个对象表示一个函数
class Dll
{
public:
    Dll();
    ~Dll();
    static Dll &Instance()
    {
        static Dll dll;
        return dll;
    }

    enum GET_CLASS_TYPE
    {
        NEWOBJECT,      //新的对象
        INSTANCE        //单例
    };

    //bool LoadLibrary(char *filename);    //默认打开的符号要立刻解释
    /*
     *  filenane 动态库的文件名
     *  funcname 函数名
     *  variable 传入的参数指针，这个指针一般是结构体指针
     *  isreset  重置则会重新加载一个库文件进来，不重置则沿用原来的库文件句柄
     *  注明：在实际运用中可以通过 static 来声明函数指针，这样就不需要每次使用这个函数都调用Func
     */
    void *Func(char *filename,char *funcname,void *variable = NULL,bool isreset = false);  //传入一个结构体变量指针，返回一个空指针

    void *Class(char *filename,char *classname,int type = INSTANCE);

    //map<char *,void *> m_librarys;
    //map<char *,void *>::iterator m_itr;
private:

    void *m_Handle;
    char *filename;
    char *funcname;
};

#endif // DLL_H
#endif