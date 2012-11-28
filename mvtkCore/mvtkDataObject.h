#ifndef __mvtkDataObject_h
#define __mvtkDataObject_h

#include "mvtkObject.h"

/// mvtkDataObject - an abstract class to represents a data object in MVTK
///////////////////////////////////////////////////////////////////////////
/// mvtkDataObject is an abstract class to represents a data object in MVTK.
/// And in MVTK, you have only two kinds of data object to deal with.
/// \see mvtkVolume
/// \see mvtkMesh
class MVTK_COMMON_API mvtkDataObject : public mvtkObject
{
public:
    MVTK_ABSTRACT_TYPE(mvtkDataObject,mvtkObject)

		virtual void PrintSelf(ostream& os){};

    ///////////////////////////////////////////////////////////////////////////
    /// Delete the allocated memory (if any) and initialize to default status.
	/// \note Pure virtual function. Its concrete subclass must implement
	/// this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void Initialize() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Return the data object type.
	/// \return Always return MVTK_DATA_OBJECT
	/// \note Pure virtual function. Its concrete subclass must implement
	/// this function and return its data object type.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const {return MVTK_DATA_OBJECT;}

 //   ///////////////////////////////////////////////////////////////////////////
 //   /// Return the actual memory size occupied by this data object. The unit is BYTE.
	///// \return Return the actual memory size occupied by this data object.
	///// The unit is BYTE.
	///// \note Pure virtual function. Its concrete subclass must implement
	///// this function and return its memory size.
 //   ///////////////////////////////////////////////////////////////////////////
 //   virtual unsigned long long GetActualMemorySize() const = 0;

    /////////////////////////////////////////////////////////////////////////////
    ///// \warning Internal function. Don't call it directly.
    /////////////////////////////////////////////////////////////////////////////
    //virtual void ShallowCopy(mvtkDataObject *src) = 0;

	/////////////////////////////////////////////////////////////////////////////
 //   /// \warning Internal function. Don't call it directly.
 //   ///////////////////////////////////////////////////////////////////////////
 //   virtual void DeepCopy(mvtkDataObject *src) = 0;    

protected:
	mvtkDataObject(){};    
	virtual ~mvtkDataObject(){};

//private:
//	mvtkDataObject(const mvtkDataObject&);
//    void operator=(const mvtkDataObject&);
};


#endif



