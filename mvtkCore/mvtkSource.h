#ifndef __mvtkSource_h
#define __mvtkSource_h

#include "mvtkProcessObject.h"

/// mvtkSource - abstract class specifies interface for source object
///////////////////////////////////////////////////////////////////////////
/// mvtkSource is an abstract object that specifies behavior and interface
/// of source objects. Source objects are creators of data objects, including
/// reader and procedual source.
class MVTK_COMMON_API mvtkSource : public mvtkProcessObject
{
public:
    MVTK_ABSTRACT_TYPE(mvtkSource,mvtkProcessObject)

	virtual void PrintSelf(ostream& os){}

protected:
	mvtkSource(){};
	virtual ~mvtkSource(){};
    
//private:
//	mvtkSource(const mvtkSource&);
//    void operator=(const mvtkSource&);

};



//#define DEFINED_mvtkSource



#endif





