#ifndef __mvtkSPMD_h
#define __mvtkSPMD_h

typedef void (*mvtkSPMDThread)(int NumberOfThreads,	int ThreadID,void* userData);

void LaunchSPMD(mvtkSPMDThread entrance,void* userData);

#endif