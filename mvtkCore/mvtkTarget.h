#ifndef __mvtkTarget_h
#define __mvtkTarget_h

#include "mvtkProcessObject.h"

/// mvtkTarget - abstract class specifies interface for Target object
///////////////////////////////////////////////////////////////////////////
/// mvtkTarget is an abstract object that specifies behavior and interface
/// of mapper objects. Mapper object representas end point for a data processing
/// pipeline, e.g. view or writer. It only accepts input data and either displays
/// the input data to a view or writes the input data to a disk file.
class MVTK_COMMON_API mvtkTarget : public mvtkProcessObject
{
public:
    MVTK_ABSTRACT_TYPE(mvtkTarget,mvtkProcessObject)

	virtual void PrintSelf(ostream& os){};

protected:
	mvtkTarget(){}
	virtual ~mvtkTarget(){}

//private:
//	mvtkTarget(const mvtkTarget&);
//    void operator=(const mvtkTarget&);

};


//#define DEFINED_mvtkTarget



#endif


