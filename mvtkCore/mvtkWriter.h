#ifndef __mvtkWriter_h
#define __mvtkWriter_h

#include "mvtkTarget.h"

//class mvtkStringList1;

/// mvtkWriter - an abstract class represents a writer
///////////////////////////////////////////////////////////////////////////
/// mvtkWriter defines the interface of all of the writers. To use a 
/// concrete writer, for example, mvtkBMPWriter, the code snippet is: 
/// \code
/// mvtkBMPWriter *aWriter = new mvtkBMPWriter; 
/// aWriter->SetInput(aVolume); 
/// int imageNum = aVolume->GetImageNum(); 
/// Gerenate file names into files[imageNum]; 
/// for(int i = 0; i < imageNum; i++) 
///		aWriter->AddFileName(files[i]); 
/// aWriter->Run(); 
/// \endcode
class MVTK_COMMON_API mvtkWriter : public mvtkTarget
{
public:
    MVTK_ABSTRACT_TYPE(mvtkWriter,mvtkTarget)

	virtual void PrintSelf(ostream& os){};

	///////////////////////////////////////////////////////////////////////
	/// Add a file into the internal list for writing these files.
	/// \param inFileName C string for the file name.	
	///////////////////////////////////////////////////////////////////////
	void AddFileName(const char *inFileName);

	///////////////////////////////////////////////////////////////////////
	/// Sort all the file names alphabetically.
	///////////////////////////////////////////////////////////////////////
	void SortFileNames();


protected:
	virtual ~mvtkWriter();
    mvtkWriter();

	int _getFileCount(void);
	const char* _getFileName(int nIndex);

    list<string>* m_FileNames;
//private:
//	mvtkWriter(const mvtkWriter&);
//    void operator=(const mvtkWriter&);
};


//#define DEFINED_mvtkWriter



#endif

