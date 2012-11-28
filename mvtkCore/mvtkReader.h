#ifndef __mvtkReader_h
#define __mvtkReader_h

#include "mvtkSource.h"

//class mvtkStringList;

/// mvtkReader - an abstract class represents a reader
///////////////////////////////////////////////////////////////////////////
/// mvtkReader defines the interface of all of the readers. To use a 
/// concrete reader, for example, mvtkBMPReader, the code snippet is: 
/// \code
/// mvtkBMPReader *aReader = new mvtkBMPReader; 
/// aReader->AddFileName(file1); 
/// aReader->AddFileName(file2); 
/// ...  ...  ... 
/// aReader->Run(); 
/// mvtkVolume *aVolume = aReader->GetOutput(); 
/// Using aVolume 
/// \endcode
class MVTK_COMMON_API mvtkReader : public mvtkSource
{
public:
    MVTK_ABSTRACT_TYPE(mvtkReader,mvtkSource)

	virtual void PrintSelf(ostream& os){};

    ///////////////////////////////////////////////////////////////////////
	/// Add a file into the internal list for reading these files.
	/// \param inFileName C string for the file name.	
	///////////////////////////////////////////////////////////////////////
	void AddFileName(const char *inFileName);

	///////////////////////////////////////////////////////////////////////
	/// Sort all the file names alphabetically.
	///////////////////////////////////////////////////////////////////////
	void SortFileNames();

	void RemoveAllFileNames();

protected:
	virtual ~mvtkReader();
    mvtkReader();

	int _getFileCount(void);
	const char* _getFileName(int nIndex);

    list<string>* m_FileNames;
//private:
//	mvtkReader(const mvtkReader&);
//    void operator=(const mvtkReader&);
};


//#define DEFINED_mvtkReader



#endif


