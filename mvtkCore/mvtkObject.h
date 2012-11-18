#ifndef __mvtkObject_h
#define __mvtkObject_h

#include "mvtkGlobal.h"

class mvtkObserver;

/// mvtkObject - abstract base class for most objects in MVTK
///////////////////////////////////////////////////////////////////////////
/// mvtkObject is the base class for most objects in MVTK. It provides several
/// base services for all of MVTK objects. \n
/// The first base service is the RTTI(Run Time Type Information). 
/// Please see the  GetClassname(), IsTypeOf(), IsA(), SafeDownCast() \n
/// The second base service is the debugging information.
/// Please see the  DebugOn(), DebugOff(), GetDebug(), SetDebug(), BreakOnError(),
/// PrintSelf() \n
/// The third base service is the memory management, including Reference Counting 
/// and Garbage Collection.
/// Please see the AddReference(), RemoveReference(), GetReferenceCount(),
/// Delete() \n
/// The fourth base service is the support of the observer design pattern, which 
/// makes the updating user interface to reflect the internal status of a MVTK
/// object possible.
/// Please see the AddObserver(), RemoveObserver(), RemoveAllObservers()
/// \note The deconstructor of mvtkObject and all of its subclasses is protected. This
/// means that a object in MVTK must be allocated in the heap using new operator. If
/// you define a local MVTK object in the stack, the compiler will generate an error
/// information. 
class MVTK_COMMON_API mvtkObject
{
public:
	static mvtkObject * New(){return new mvtkObject;}
    ///////////////////////////////////////////////////////////////////////////
    /// Get the class name as a string. The purpose is to support RTTI.
	/// \return Return the class name of this object. For mvtkObject, it always 
	/// return "mvtkObject"
    ///////////////////////////////////////////////////////////////////////////
    virtual const char *GetClassname() const {return "mvtkObject";}

    ///////////////////////////////////////////////////////////////////////////
    /// Decide if this class is one type of the specified class
	/// \param name The name of specified class 
	/// \return Return 1 if this class is the same type of (or a subclass of)
    /// the specified class. Returns 0 otherwise.
    ///////////////////////////////////////////////////////////////////////////
    static int IsTypeOf(const char *name);

    ///////////////////////////////////////////////////////////////////////////
    /// Decide if this class is one type of the specified class
	/// \param name The name of specified class
	/// \return Return 1 if this class is the same type of (or a subclass of)
    /// the specified class. Returns 0 otherwise.
    ///////////////////////////////////////////////////////////////////////////
    virtual int IsA(const char *name);

    ///////////////////////////////////////////////////////////////////////////
    /// Safely cast the specified object to mvtkObject*
	/// \param o The specified object
	/// \return If success, return the casted o, otherwise return NULL.
    ///////////////////////////////////////////////////////////////////////////
    static mvtkObject *SafeDownCast(mvtkObject *o);

    ///////////////////////////////////////////////////////////////////////////
    /// Turn debugging output on.
    ///////////////////////////////////////////////////////////////////////////
    virtual void DebugOn();

    ///////////////////////////////////////////////////////////////////////////
    /// Turn debugging output off.
    ///////////////////////////////////////////////////////////////////////////
    virtual void DebugOff();

    ///////////////////////////////////////////////////////////////////////////
    /// Get the value of the debug flag.
	/// \return Return zero, the debug flag is off, otherwise the debug flag is on.
    ///////////////////////////////////////////////////////////////////////////
    unsigned char GetDebug();

    ///////////////////////////////////////////////////////////////////////////
    /// Set the value of the debug flag.
	/// \param debugFlag If debugFlag is zero, set the debug flag to off, otherwise
	/// set the debug flag to on.
    ///////////////////////////////////////////////////////////////////////////
    void SetDebug(unsigned char debugFlag);

    ///////////////////////////////////////////////////////////////////////////
    /// This method is called when mvtkErrorMessage executes.
    ///////////////////////////////////////////////////////////////////////////
    static void BreakOnError();

    ///////////////////////////////////////////////////////////////////////////
    /// Print this object to an ostream.
	/// \param os The specified ostream to output information.
    ///////////////////////////////////////////////////////////////////////////
    void Print(ostream& os);

    ///////////////////////////////////////////////////////////////////////////
    /// Print the necessary information about this object for the debugging purpose.
	/// \param os The specified ostream to output information.
    ///////////////////////////////////////////////////////////////////////////
    virtual void PrintSelf(ostream& os);

	///////////////////////////////////////////////////////////////////////
	/// Attach an observer to this object.
	/// \param observer pointer to an mvtkObserver to attach
	///////////////////////////////////////////////////////////////////////
	void AddObserver(mvtkObserver *observer);

	///////////////////////////////////////////////////////////////////////
	/// Detach an observer from this object.
	/// \param observer pointer to an mvtkObserver to detach
	///////////////////////////////////////////////////////////////////////
	void RemoveObserver(mvtkObserver *observer);

	///////////////////////////////////////////////////////////////////////
	/// Detach all observers from this object.
	///////////////////////////////////////////////////////////////////////
	void RemoveAllObservers();

	///////////////////////////////////////////////////////////////////////
	/// Add 1 to the referenct count. Only when the reference count of a MVTK
	/// object is equal to 0, it can be deleted.	
	///////////////////////////////////////////////////////////////////////
	void AddReference();

    ///////////////////////////////////////////////////////////////////////
	/// Remove 1 to the referenct count. If reference count is equal to zero
	/// after remove 1, then this object is deleted automatically.
	///////////////////////////////////////////////////////////////////////
	void RemoveReference();

    ///////////////////////////////////////////////////////////////////////
	/// Get current referenct count of this object. Only when the reference
	/// count of a MVTK object is equal to 0, it can be deleted.	
	/// \return Return the reference count of this object.
	///////////////////////////////////////////////////////////////////////
	int  GetReferenceCount()    {return m_ReferenceCount;}
	
	///////////////////////////////////////////////////////////////////////
	/// If current reference count is equal to 0, delete this object, otherwise,
	/// nothing happens. 
	/// \note Usually a MVTK object can only be deleted through two ways. One 
	/// is to call RemoveReference(), and the other is to call Delete(). But
	/// RemoveReference() is usually called internally to implement the reference
	/// counting design pattern, so Delete() is the correct function to call
	/// if you want to delete a MVTK object.
	///////////////////////////////////////////////////////////////////////
	void Delete();

protected:
    mvtkObject();    
	virtual ~mvtkObject();

	void _updateObservers();

    int m_Debug;     // Enable debug messages
	int m_ReferenceCount;

	list<mvtkObserver*>* m_Observers;

//private:
//
//    friend ostream& operator << (ostream& os, mvtkObject& o);
//	mvtkObject(const mvtkObject&);
//    void operator = (const mvtkObject&);
};

 
//#define DEFINED_mvtkObject



#endif


