#ifndef __mvtkGlobal_h
#define __mvtkGlobal_h

#include "mvtkCommonIncludes.h"
#include <math.h>
#include <assert.h>

#include <string.h>

#ifdef MVTK_OS_LINUX
#include <strings.h>
#define stricmp strcasecmp
#endif

//I/O Stream & string
#include <iostream> 
#include <sstream>
#include <fstream>  
#include <iomanip>  
#include <string> 
#include <vector>
#include <list>

// Need these in global namespace so the same code will work with ansi
// and old-style streams.
using std::dec;
using std::hex;
using std::setw;
using std::setfill;
using std::cerr;
using std::cout;
using std::cin;
using std::ios;
using std::endl;
using std::ostream;
using std::istream;
using std::ostringstream;
using std::istringstream;
using std::stringstream;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::string;
using std::vector;
using std::list;

typedef unsigned int index_type;
typedef unsigned int size_type;

typedef string mvtkString;
typedef vector<string> mvtkStringList;

// Some constants used throughout the code
#define MVTK_LARGE_FLOAT 1.0e+38F
#define MVTK_LARGE_INTEGER 2147483647 // 2^31 - 1

// These types are returned by GetDataType to indicate pixel type.
#define MVTK_VOID            0
#define MVTK_BIT             1
#define MVTK_CHAR            2
#define MVTK_UNSIGNED_CHAR   3
#define MVTK_SHORT           4
#define MVTK_UNSIGNED_SHORT  5
#define MVTK_INT             6
#define MVTK_UNSIGNED_INT    7
#define MVTK_LONG            8
#define MVTK_UNSIGNED_LONG   9
#define MVTK_FLOAT          10
#define MVTK_DOUBLE         11
//
////变量数组初始化宏
//#define AllocateMacro(d,t,s) \
//	switch(t){ \
//		case MVTK_VOID:			return; \
//		case MVTK_BIT:			return; \
//		case MVTK_CHAR:			d=new char[s];break; \
//		case MVTK_UNSIGNED_CHAR:d=new unsigned char[s];break; \
//		case MVTK_SHORT:		d=new short[s];break; \
//		case MVTK_UNSIGNED_SHORT:d=new unsigned short[s];break; \
//		case MVTK_INT:			d=new int[s];break; \
//		case MVTK_UNSIGNED_INT:	d=new unsigned int[s];break; \
//		case MVTK_LONG:			d=new long[s];break; \
//		case MVTK_UNSIGNED_LONG:d=new unsigned long[s];break; \
//		case MVTK_FLOAT:		d=new float[s];break; \
//		case MVTK_DOUBLE:		d=new double[s];break; \
//		default:return; \
//} \

// Some constant required for correct template performance
#define MVTK_BIT_MIN 0
#define MVTK_BIT_MAX 1
#define MVTK_CHAR_MIN -128
#define MVTK_CHAR_MAX 127
#define MVTK_UNSIGNED_CHAR_MIN 0
#define MVTK_UNSIGNED_CHAR_MAX 255
#define MVTK_SHORT_MIN -32768
#define MVTK_SHORT_MAX 32767
#define MVTK_UNSIGNED_SHORT_MIN 0
#define MVTK_UNSIGNED_SHORT_MAX 65535
#define MVTK_INT_MIN (-MVTK_LARGE_INTEGER-1)
#define MVTK_INT_MAX MVTK_LARGE_INTEGER
#define MVTK_UNSIGNED_INT_MIN 0
#define MVTK_UNSIGNED_INT_MAX 4294967295UL
#define MVTK_LONG_MIN (-MVTK_LARGE_INTEGER-1)
#define MVTK_LONG_MAX MVTK_LARGE_INTEGER
#define MVTK_UNSIGNED_LONG_MIN 0
#define MVTK_UNSIGNED_LONG_MAX 4294967295UL
#define MVTK_FLOAT_MIN -MVTK_LARGE_FLOAT
#define MVTK_FLOAT_MAX MVTK_LARGE_FLOAT
#define MVTK_DOUBLE_MIN -1.0e+99L
#define MVTK_DOUBLE_MAX  1.0e+99L

// These types are returned to distinguish data object types
#define MVTK_DATA_OBJECT                 0
#define MVTK_VOLUME                   1000
#define MVTK_IC_VOLUME                1001
#define MVTK_OOC_VOLUME               1002
#define MVTK_PARALLEL_PROJECT_DATA    1003
#define MVTK_OUT_OF_CORE_PARALLEL_PROJECT_DATA  1004
#define MVTK_COHERENT_VOLUME		  1005

#define MVTK_MESH                     2000
#define MVTK_TRIANGLE_MESH            2001
#define MVTK_IC_TRIANGLE_MESH         2002
#define MVTK_OOC_TRIANGLE_MESH        2003
#define MVTK_HE_MESH                  2004
#define MVTK_HE_TRIANGLE_MESH         2005
#define MVTK_HE_IC_TRIANGLE_MESH      2006
#define MVTK_HE_OOC_TRIANGLE_MESH     2007

#define MVTK_RAW_DATA				  3000
#define MVTK_CT_PROJECTION_DATA		  3001
#define MVTK_2D_BEAM_PD			      3002
#define MVTK_2D_BEAM_IC_PD			  3003
#define MVTK_2D_BEAM_OOC_PD			  3004
#define MVTK_2D_BEAM_REAL_TIME_PD     3005
#define MVTK_CONE_BEAM_PD			  3006
#define MVTK_CONE_BEAM_IC_PD		  3007
#define MVTK_CONE_BEAM_OOC_PD		  3008
#define MVTK_CONE_BEAM_REAL_TIME_PD   3009
#define MVTK_TRACKED_BSCAN_DATA		  3010
#define MVTK_TRACKED_BSCAN_IC_DATA	  3011
#define MVTK_TRACKED_BSCAN_OOC_DATA	  3012


#define MVTK_IMAGE                    5001
#define MVTK_PIECEWISE_FUNCTION       5002
#define MVTK_IMAGE_DATA               5003
#define MVTK_IMAGE_RAWCT              5004
#define MVTK_POLY_DATA                5005
#define MVTK_RAWCT_DATA               5006

#define MVTK_LEFTBUTTON    0
#define MVTK_MIDDLEBUTTON  1
#define MVTK_RIGHTBUTTON   2

#define MVTK_CTRLKEY         0
#define MVTK_SHIFTKEY        1
#define MVTK_CTRLANDSHIFTKEY 2

#define MVTK_NEAREST_INTERPOLATION 0
#define MVTK_LINEAR_INTERPOLATION  1 
#define MVTK_BILINEAR_INTERPOLATION 2

#define MVTK_FLOAT_PI  3.14159265358979323846f
#define MVTK_DOUBLE_PI 3.14159265358979323846
//
// These swap macros are used for processing endian problem
//
#define	Swap16(shortX) shortX = ((shortX & 0x00FF) << 8) | ((shortX & 0xFF00) >> 8)

#define	Swap32(intX) \
	  intX = ((intX & 0x000000FF) << 24) \
	       | ((intX & 0x0000FF00) << 8) \
		   | ((intX & 0x00FF0000) >> 8) \
		   | ((intX & 0xFF000000) >> 24)

#define Swap64(lowX,highX) \
{     Swap32(lowX); \
	  Swap32(highX); \
	  unsigned long swaptmp = lowX; \
	  lowX = highX; \
	  highX = swaptmp; \
}

//取小头
//
// Macro for floor of x
//
#define mvtkFloorFuncMacro(x)   (((x) < 0.0)?((int)((x)-1.0)):((int)(x)))

//取大头
//
// Macro for rounding x
//
#define mvtkRoundFuncMacro(x)   (int)((x)+0.5)

//
// Macro for tri-linear interpolation - do four linear interpolations on
// edges, two linear interpolations between pairs of edges, then a final
// interpolation between faces
//
#define mvtkTrilinFuncMacro(v,x,y,z,a,b,c,d,e,f,g,h)         \
{       t00 =   a + (x)*(b-a);      \
        t01 =   c + (x)*(d-c);      \
        t10 =   e + (x)*(f-e);      \
        t11 =   g + (x)*(h-g);      \
        t0  = t00 + (y)*(t01-t00);  \
        t1  = t10 + (y)*(t11-t10);  \
        v   =  t0 + (z)*(t1-t0); }
//信息提示宏
//
// This macro is used for  print information in non-member methods
// mvtkGenericMessage("this is debug info" << this->SomeVariable);
//
#define mvtkGenericMessage(x) \
{     ostringstream mvtkmsg; \
      mvtkmsg << x << "\n"; \
      mvtkDisplayMessage(mvtkmsg.str().c_str());}

//
// This macro is used to print out debug message in a member function
// of mvtkObject derived class
// mvtkDebugMessage("this is debug info" << this->SomeVariable);
//
#define mvtkDebugMessage(x) \
{ if (this->m_Debug ) \
    { ostringstream mvtkmsg; \
      mvtkmsg << "Debug: In " __FILE__ ", line " << __LINE__ << "\n" << this->GetClassname() << " (" << this << "): " << x  << "\n\n"; \
      mvtkDisplayMessage(mvtkmsg.str().c_str());}}

//
// This macro is used to print out warning message in a member function
// of mvtkObject derived class
// mvtkWarningMessage("Warning message" << variable);
//
#define mvtkWarningMessage(x) \
{     ostringstream mvtkmsg; \
      mvtkmsg << "Warning: In " __FILE__ ", line " << __LINE__ << "\n" << this->GetClassname() << " (" << this << "): " << x << "\n\n"; \
      mvtkDisplayMessage(mvtkmsg.str().c_str());}

//
// This macro is used to print out error message in a member function
// of mvtkObject derived class
// mvtkErrorMessage("Error message" << variable);
//
#define mvtkErrorMessage(x) \
{     ostringstream mvtkmsg; \
      mvtkmsg << "ERROR: In " __FILE__ ", line " << __LINE__ << "\n" << this->GetClassname() << " (" << this << "): " << x << "\n\n"; \
      mvtkDisplayMessage(mvtkmsg.str().c_str());\
      mvtkObject::BreakOnError();}

//类信息生成宏_虚类_不包含new方法
#define MVTK_ABSTRACT_TYPE(thisClass,superclass) \
  virtual const char *GetClassname() const {return #thisClass;} \
  static int IsTypeOf(const char *type) \
  { \
    if ( !strcmp(#thisClass,type) ) \
      { \
      return 1; \
      } \
    return superclass::IsTypeOf(type); \
  } \
  virtual int IsA(const char *type) \
  { \
    return this->thisClass::IsTypeOf(type); \
  } \
  static thisClass* SafeDownCast(mvtkObject *o) \
  { \
    if ( o && o->IsA(#thisClass) ) \
      { \
      return static_cast<thisClass *>(o); \
      } \
    return NULL;\
  } \
//类信息生成宏_标准_包含new方法
#define MVTK_TYPE(thisClass,superclass) \
	virtual const char *GetClassname() const {return #thisClass;} \
	static int IsTypeOf(const char *type) \
  { \
  if ( !strcmp(#thisClass,type) ) \
	  { \
	  return 1; \
	  } \
	  return superclass::IsTypeOf(type); \
  } \
  virtual int IsA(const char *type) \
  { \
  return this->thisClass::IsTypeOf(type); \
  } \
  static thisClass* SafeDownCast(mvtkObject *o) \
  { \
  if ( o && o->IsA(#thisClass) ) \
	  { \
	  return static_cast<thisClass *>(o); \
	  } \
	  return NULL;\
  } \
  static thisClass* New() \
  { \
  return new thisClass; \
  }
//加了New方法到公共宏 mvtkObject 和 mvtkList例外

MVTK_COMMON_API char const* mvtkGetDataTypeName(int dataType); 
MVTK_COMMON_API int mvtkGetDataTypeFromName(char const *name);
MVTK_COMMON_API int mvtkGetDataTypeBits(int dataType);
MVTK_COMMON_API int mvtkGetDataTypeSize(int dataType);
MVTK_COMMON_API double mvtkGetDataTypeMin(int dataType);
MVTK_COMMON_API double mvtkGetDataTypeMax(int dataType);

#include "mvtk_utilities/mvtk_nl/mvtk_nl_vector.h"

typedef double					ScalarParameterType;
typedef float					ScalarPixelType;
typedef int						ScalarIndexType;
typedef mvtk_nl_vector<double>	VectorParameterType;
typedef mvtk_nl_vector<float>	VectorPixelType;
typedef mvtk_nl_vector<int>		VectorIndexType;

#define MVTK_VER_OOC

#endif


