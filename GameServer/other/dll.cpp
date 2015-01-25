#include "dll.h"

#ifdef _linux

Dll::Dll()
{
    m_Handle = NULL;
}

Dll::~Dll()
{
    if (m_Handle != NULL)
    {
         dlclose(m_Handle);
         m_Handle = NULL;
    }
}


void *Dll::Func(char *filename, char *funcname, void *variable, bool isreset)
{
    if (isreset)
    {
        dlclose(m_Handle);
        m_Handle = NULL;
    }
    if (m_Handle == NULL)
    {
        m_Handle = dlopen(filename,RTLD_NOW);
        if (m_Handle == NULL)
        {
            printf("Load library failed!\n");
            printf("%s\n",dlerror());
            return NULL;
        }
    }
    if (variable == NULL)
    {
        void *(*function)() = NULL;
        function = (void* (*)())dlsym(m_Handle,funcname);
        if (dlerror())
        {
            printf ("Cannot load symbol destroy: %s\n",dlerror());
            return NULL;
        }
        return (void *)function;
    }
    else
    {
        void *(*function)(void *) = NULL;
        function = (void* (*)(void *))dlsym(m_Handle,funcname);
        if (dlerror())
        {
            printf ("Cannot load symbol destroy: %s\n",dlerror());
            return NULL;
        }
        return (void *)function;
    }

}


//暂时没有用
void *Dll::Class(char *filename, char *classname, int type)
{
    if (m_Handle == NULL)
    {
        m_Handle = dlopen(filename,RTLD_NOW);
        if (m_Handle == NULL)
        {
            printf("Load library failed!\n");
            printf("%s\n",dlerror());
            return NULL;
        }
    }
    if(type == NEWOBJECT)
    {

    }
    else if(type == INSTANCE)
    {
        void *function;
        function = (void *) dlsym(m_Handle,"jjiiaa");
        if (dlerror())
        {
            printf ("Cannot load symbol destroy: %s\n",dlerror());
            return NULL;
        }
        return function;
    }
}



#endif





