#ifndef __mvtkVolumeReader_h
#define __mvtkVolumeReader_h

#include "mvtkReader.h"

class mvtkVolume;
//class mvtkString;

/// mvtkVolumeReader - an abstract class represents a volume reader to read image/volume files
///////////////////////////////////////////////////////////////////////////
/// mvtkVolumeReader defines the interface of all of the volume readers.
/// To use a concrete volume reader, for example, mvtkBMPReader, the code
/// snippet is: 
/// \code
/// mvtkBMPReader *aReader = new mvtkBMPReader; 
/// aReader->AddFileName(file1); 
/// aReader->AddFileName(file2); 
/// ...  ...  ... 
/// if (aReader->Run())
/// { 
///		mvtkVolume *aVolume = aReader->GetOutput(); 
///		Using aVolume
/// }
/// \endcode
class MVTK_COMMON_API mvtkVolumeReader : public mvtkReader
{
public:
	MVTK_ABSTRACT_TYPE(mvtkVolumeReader,mvtkReader)

	virtual void PrintSelf(ostream& os){};

	///////////////////////////////////////////////////////////////////////
	/// Get the output volume the reader has read.
	/// \return the output volume.
	///////////////////////////////////////////////////////////////////////
	mvtkVolume* GetOutput(){return this->m_OutData;}

	void SetFilePattern(char* filePattern);

	//ÑÓ³Ù¼ÓÔØ×÷ÓÃ
	virtual void Update()=0;

protected:
	mvtkVolumeReader();
	virtual ~mvtkVolumeReader();

	mvtkVolume *m_OutData;

	string *m_FilePattern;
	//unsigned int m_BufferedSliceNum;

	//private:
	//	mvtkVolumeReader(const mvtkVolumeReader&);
	//    void operator=(const mvtkVolumeReader&);

};


//#define DEFINED_mvtkVolumeReader



#endif


