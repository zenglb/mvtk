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

	///////////////////////////////////////////////////////////////////////
	/// Set spacing information in x axis, the unit is mm.
	/// \param px the spacing (mm) in two adjacent voxels in x axis.
	///////////////////////////////////////////////////////////////////////	
	void SetSpacingX(float px){ m_Spacings[0] = px ;}

	///////////////////////////////////////////////////////////////////////
	/// Set spacing information in y axis, the unit is mm.
	/// \param py the spacing (mm) in two adjacent voxels in y axis.
	///////////////////////////////////////////////////////////////////////	
	void SetSpacingY(float py){ m_Spacings[1] = py ;}

	///////////////////////////////////////////////////////////////////////
	/// Set spacing information in z axis, the unit is mm.
	/// \param pz the spacing (mm) in two adjacent voxels in z axis.
	///////////////////////////////////////////////////////////////////////	
	void SetSpacingZ(float pz){ m_Spacings[2] = pz ;}

	///////////////////////////////////////////////////////////////////////
	/// Set spacing information in x, y, z axis respectively, the unit is mm.
	/// \param px the spacing (mm) in two adjacent voxels in x axis.
	/// \param py the spacing (mm) in two adjacent voxels in y axis.
	/// \param pz the spacing (mm) in two adjacent voxels in z axis.
	///////////////////////////////////////////////////////////////////////
	void SetSpacings(float s[3])
	{
		m_Spacings[0] = s[0];
		m_Spacings[1] = s[1];
		m_Spacings[2] = s[2];
	}

	//ÑÓ³Ù¼ÓÔØ×÷ÓÃ
	virtual void Update()=0;

	void SetImgProgressMethod(void (* f) (void*,void*,int,int,int,int&,int&)){m_ImgProgressMethod = f;}

protected:
	mvtkVolumeReader();
	virtual ~mvtkVolumeReader();

	mvtkVolume *m_OutData;

	float m_Spacings[3];

	string *m_FilePattern;

	void (* m_ImgProgressMethod) (void* src_img,void* des_img,int MVTK_DataType,int src_w,int src_h,int& des_w,int& des_h);
	//unsigned int m_BufferedSliceNum;

	//private:
	//	mvtkVolumeReader(const mvtkVolumeReader&);
	//    void operator=(const mvtkVolumeReader&);

};


//#define DEFINED_mvtkVolumeReader



#endif


