
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <Windows.h>
#endif

#include "thread.h"

bool Thread::Create(void *func(void *), void *arg)
{  
#ifdef __unix
	 int err = pthread_create(&m_thread, NULL, func, arg);
	 if (err != 0)
	 {
		 printf("can't create thread: %s\n", strerror(err));
		 return false;
	 }
#endif
#ifdef WIN32
	 m_thread = ::CreateThread(NULL, 0, ( LPTHREAD_START_ROUTINE )func, arg, 0, NULL);
	 if (m_thread == NULL)
	 {
		printf("can't create thread\n"); 
		return false;
	 }
#endif
	 return true;
}

bool Thread::Join()
{
#ifdef __unix
	if (m_thread != 0)
	{
		void *v;
		int ret = pthread_join(m_thread, &v);
		if (ret == 0)
		{
			m_thread = 0;
		}

		return ret == 0;
	}
#endif
#ifdef WIN32
	if (WaitForSingleObject(m_thread, INFINITE) == WAIT_OBJECT_0)
	{
		CloseHandle(m_thread);
		m_thread = NULL;
		return true;
	}
#endif
	return false;
}



