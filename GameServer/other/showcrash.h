#ifndef SHOWCRASH_H
#define SHOWCRASH_H

#ifdef __LINUX__
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <execinfo.h>
#include <string>
#include "global/globalvariable.h"
#include "global/globalfunction.h"
using namespace std;


class ShowCrash
{
public:
    ShowCrash();

    static void CrashFunction(int);

    static const int MAX_JMP_BUF = 16;

    static const int MAX_CALLSTACK_DEPTH = 32;

    enum buffername
    {
        BUF_MAIN ,
        BUF_COUNT
    };


private:


};

extern int buf_index;

#define SETJMP(index)\
    setjmp(buff[index]);\
    buf_index = index;\


extern ShowCrash g_showcrash;
extern jmp_buf buff[ShowCrash::MAX_JMP_BUF];

#endif
#endif
