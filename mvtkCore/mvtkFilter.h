#ifndef __mvtkFilter_h
#define __mvtkFilter_h

#include "mvtkProcessObject.h"

/// mvtkFilter - abstract class specifies interface for filter object
///////////////////////////////////////////////////////////////////////////
/// mvtkFilter is an abstract object that specifies behavior and interface
/// of filter objects. Filter object representation a algorithm that process
/// input data and return the output data.
class MVTK_COMMON_API mvtkFilter : public mvtkProcessObject
{
public:
	MVTK_ABSTRACT_TYPE(mvtkFilter,mvtkProcessObject)

	virtual void PrintSelf(ostream& os){};

protected:
	mvtkFilter(){};
	virtual ~mvtkFilter(){};

//private:
//	mvtkFilter(const mvtkFilter&);
//	void operator=(const mvtkFilter&);
};

#endif


