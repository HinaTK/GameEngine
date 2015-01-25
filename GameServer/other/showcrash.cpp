#include "showcrash.h"

#ifdef __LINUX__

ShowCrash g_showcrash;
jmp_buf buff[ShowCrash::MAX_JMP_BUF];
int buf_index;

ShowCrash::ShowCrash()
{
    struct sigaction act, oact;
    act.sa_handler = CrashFunction;
    sigemptyset(&act.sa_mask); //清空此信号集
    act.sa_flags = SA_NODEFER;
    sigaction(SIGINT, &act, &oact);
    sigaction(SIGABRT, &act, &oact);
    sigaction(SIGSEGV, &act, &oact);
    sigaction(SIGFPE, &act, &oact);
    sigaction(SIGBUS, &act, &oact);
    sigaction(SIGTRAP,&act,&oact);
}

void ShowCrash::CrashFunction(int)
{
    static void *traceback[MAX_CALLSTACK_DEPTH];
    static string cmd;
    if (cmd.length() <= 0)
    {
        ProgramName name;
        GLOBALFUNCTION::GetProgramName(name);
        string temp = name;
        cmd  =  "addr2line -f -e " + temp;
    }

    FILE *fp = popen(cmd.c_str(), "w");
    int depth = backtrace(traceback, MAX_CALLSTACK_DEPTH);
    for (int i = 0; i < depth && i < MAX_CALLSTACK_DEPTH; i++)
    {
        fprintf(fp, "%p\n", traceback[i]);
    }
    fclose(fp);
    longjmp(buff[buf_index],1);
}

#endif
