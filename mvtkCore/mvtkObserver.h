#ifndef __mvtkObserver_h
#define __mvtkObserver_h

#include "mvtkObject.h"

/// mvtkObserver - abstract base class for observers
///////////////////////////////////////////////////////////////////////////
/// mvtkObserver is an abstract class for observers. All mvtkObjects can
/// attach observers. You can derive from this class to get an actual 
/// observer processing the interaction between an mvtkObject and the user
/// interface.
class MVTK_COMMON_API mvtkObserver : public mvtkObject
{
public:
	MVTK_ABSTRACT_TYPE(mvtkObserver, mvtkObject)

	virtual void PrintSelf(ostream &os){};

	///////////////////////////////////////////////////////////////////////
	/// Update the observer according to the changes of the mvtkObject it
	/// is attached to. A working observer should implement this pure virtual
	/// function.
	///////////////////////////////////////////////////////////////////////
	virtual void Update() = 0;

protected:
	mvtkObserver(){};
	virtual ~mvtkObserver(){};

//private:
//	mvtkObserver(const mvtkObserver&);
//	void operator = (const mvtkObserver&);

};

#endif

