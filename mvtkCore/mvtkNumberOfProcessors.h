#ifndef __mvtkNumberOfProcessors_h
#define __mvtkNumberOfProcessors_h

#include "mvtkGlobal.h"

#if defined(WIN32)
#include "windows.h"
static int GetNumberOfProcessors()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	return sysInfo.dwNumberOfProcessors;
}
#else

#include <unistd.h>
static int GetNumberOfProcessors()
{
	int num=1;
#ifdef _SC_NPROCESSORS_ONLN
    num = sysconf( _SC_NPROCESSORS_ONLN );
#elif defined(_SC_NPROC_ONLN)
    num = sysconf( _SC_NPROC_ONLN );
#endif
#if defined(__SVR4) && defined(sun) && defined(PTHREAD_MUTEX_NORMAL)
    pthread_setconcurrency(num);
#endif
	return num;
}

#endif


#endif