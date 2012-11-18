// The mvtkCommonIncludes centralizes the inclusion of system include
// files. 

#ifndef __mvtkCommonIncludes_h
#define __mvtkCommonIncludes_h

//
//OS-----------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#define MVTK_OS_WIN32
#elif defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
	#define MVTK_OS_WIN32
	#define MVTK_OS_WIN64
#elif defined(MSDOS) || defined(_MSDOS)
	#define MVTK_OS_MSDOS
#elif defined(__linux__) || defined(__linux)
	#define MVTK_OS_LINUX
#elif defined(__APPLE__) && defined(__GNUC__)
	#define MVTK_OS_MACX
#elif defined(__MACOSX__)
	#define MVTK_OS_MACX
#elif defined(macintosh)
	#define MVTK_OS_MAC9
#elif defined(__OS2__)
	#if defined(__EMX__)
		#define MVTK_OS_OS2EMX
	#else
		#define MVTK_OS_OS2
	#endif
#elif defined(__sun) || defined(sun)
	#define MVTK_OS_SOLARIS
#elif defined(hpux) || defined(__hpux)
	#define MVTK_OS_HPUX
#elif defined(__FreeBSD__)
	#define MVTK_OS_FREEBSD
	#define MVTK_OS_BSD4
#endif

#if defined(MVTK_OS_MAC9) || defined(MVTK_OS_MACX)
#define MVTK_OS_MAC
#endif

#if defined(MVTK_OS_MAC9) || defined(MVTK_OS_MSDOS) || defined(MVTK_OS_OS2) || defined(MVTK_OS_WIN32) || defined(MVTK_OS_WIN64)
#undef MVTK_OS_UNIX
#elif !defined(MVTK_OS_UNIX)
#define MVTK_OS_UNIX
#endif

//
//Thread API-----------------------------------------------------------------

#ifndef MVTK_USE_WIN32_THREADS
#ifndef MVTK_USE_PTHREAD

#ifdef MVTK_OS_WIN32
#define MVTK_USE_WIN32_THREADS
#endif 

#ifdef MVTK_OS_LINUX
#define MVTK_USE_PTHREAD
#endif 

#endif
#endif

//
//Compiler----------------------------------------------------------------
#if defined(_MSC_VER)
	#define MVTK_CC_MSVC
	//Visual C++.Net issues for _MSC_VER >= 1300 
	#if _MSC_VER >= 1300
		#define MVTK_CC_MSVC_NET
	#endif  // _MSC_VER >= 1300
#elif defined(__BORLANDC__) || defined(__TURBOC__)
	#define MVTK_CC_BORLAND
#elif defined(__GNUC__)
	#define MVTK_CC_GNU	
#elif defined(__INTEL_COMPILER)
	#define MVTK_CC_INTEL
#endif



//
// Dll export------------------------------------------
#if defined(MVTK_OS_WIN32)  // Windows system 
#define _WIN32_WINNT 0x0501   // for Mouse Wheel support
#include <windows.h>
	#if defined(MVTK_COMMON_DLL)  //Create a DLL library
		#define MVTK_COMMON_API __declspec(dllexport)
		#define MVTK_COMMON_DLL_EXPORT
	#elif !defined(MVTK_STATIC)	//Use a DLL library
		#define MVTK_COMMON_API __declspec(dllimport)
		#define MVTK_COMMON_DLL_EXPORT
		#if defined(MVTK_CC_MSVC_NET)
			#define MVTK_TEMPLATE extern
		#else
			#define MVTK_TEMPLATE
		#endif
	#endif
#else   //Other system
#undef MVTK_COMMON_DLL
#endif

#ifndef MVTK_COMMON_API
	#define MVTK_COMMON_API
#endif

//
// Default os-dependent const values
#if defined(MVTK_OS_WIN32)
	#define MVTK_DEFAULT_TEMP_PATH getenv("TEMP")
#elif defined(MVTK_OS_LINUX)
	#define MVTK_DEFAULT_TEMP_PATH "/tmp/"
#endif

//
// Handle MSVC compiler warning messages, etc.-------------------------
#if defined(MVTK_CC_MSVC)

//disable warnings on 255 char debug symbols
#pragma warning (disable : 4786)

//disable warnings on extern before template instantiation
#pragma warning (disable : 4231)

//disable warnings on needs to have dll-interface to be used by clients of class
#pragma warning (disable : 4251)

#pragma warning (disable : 4018)

#pragma warning ( disable : 4244 )

#pragma warning ( disable : 4996 )

//#pragma warning ( disable : 4127 )
//#pragma warning ( disable : 4305 )
//#pragma warning ( disable : 4309 )
//#pragma warning ( disable : 4710 )
//#pragma warning ( disable : 4706 )
//#pragma warning ( disable : 4097 )

#endif  //_MSC_VER



//include  generic stuff-------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

static inline void mvtkDisplayMessage(const char *msgBuf)
{
    #if defined(MVTK_OS_WIN32)
	    const char *title = "Information";
        MessageBox(NULL, (LPCTSTR)msgBuf, (LPCTSTR)title, MB_OK);
    #else
        printf("%s", msgBuf);
    #endif
}

#if defined(MVTK_OS_WIN32)
#include <direct.h>
static inline  bool mvtkMakeDirectory(const char *dirname)
{
	return (_mkdir(dirname)==0);
}
static inline bool mvtkRemoveDirectory(const char *dirname)
{
	return (_rmdir(dirname)==0);
}
#else
#include <sys/stat.h>
static inline bool mvtkMakeDirectory(const char *dirname)
{
	return (mkdir(dirname,S_IRUSR | S_IWUSR | S_IXUSR)==0);
}
static inline bool mvtkRemoveDirectory(const char *dirname)
{
	return (remove(dirname)==0);
}
#endif

#endif

