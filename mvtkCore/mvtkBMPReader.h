#ifndef __mvtkBMPReader_h
#define __mvtkBMPReader_h

#include "mvtkVolumeReader.h"

/// mvtkBMPReader - a concrete reader for reading BMP image files
///////////////////////////////////////////////////////////////////////////
/// mvtkBMPReader reads a set of BMP image files to a volume. Because BMP
/// file doesn't have the spacing information, you must set them using the
/// SetSpacingX, SetSpacingY, SetSpacingZ functions. To use this reader,
/// the code snippet is: 
/// \code
/// mvtkBMPReader *aReader = new mvtkBMPReader; 
/// aReader->SetSpacingX(sx); 
/// aReader->SetSpacingY(sy); 
/// aReader->SetSpacingZ(sz); 
/// aReader->AddFileName(file1);
/// aReader->AddFileName(file2);
/// ...  ...  ... 
/// if (aReader->Run())
/// { 
///		mvtkVolume *aVolume = aReader->GetOutput(); 
///		Using aVolume
/// }
/// \endcode
/// \warning All of the images must have equal width and height. Otherwise
/// they can't form a volume. Now MVTK only supports 8 bits and 24 bits 
/// BMP files.
class MVTK_COMMON_API mvtkBMPReader : public mvtkVolumeReader
{
public:
	MVTK_TYPE(mvtkBMPReader,mvtkVolumeReader)

	virtual void PrintSelf(ostream& os){};

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

	virtual void Update();

	void SetImgProgressMethod(void (* f) (void*,void*,int,int,int,int&,int&)){m_ImgProgressMethod = f;}

protected:
	mvtkBMPReader();
	virtual ~mvtkBMPReader();    

#pragma pack(2)
	typedef struct tagBITMAPFILEHEADER
	{ 
		unsigned short    bfType; 
		unsigned long   bfSize; 
		unsigned short    bfReserved1; 
		unsigned short    bfReserved2; 
		unsigned long   bfOffBits; 
	} BITMAPFILEHEADER;
#pragma pack()	


	typedef struct tagBITMAPINFOHEADER
	{
		unsigned long  biSize; 
		unsigned long   biWidth; 
		unsigned long   biHeight; 
		unsigned short   biPlanes; 
		unsigned short   biBitCount; 
		unsigned long  biCompression; 
		unsigned long  biSizeImage; 
		unsigned long   biXPelsPerMeter; 
		unsigned long   biYPelsPerMeter; 
		unsigned long  biClrUsed; 
		unsigned long  biClrImportant; 
	} BITMAPINFOHEADER;

	typedef struct tagRGBQUAD{//调色板定义
		unsigned char rgbBlue; 
		unsigned char rgbGreen;
		unsigned char rgbRed;
		unsigned char rgbReserved;
	}RGBQUAD;


	//typedef struct tag_bmp_core_header
	//{
	//	unsigned long	bcSize; 
	//	unsigned short	bcWidth; 
	//	unsigned short	bcHeight; 
	//	unsigned short	bcPlanes; 
	//	unsigned short	bcBitCount; 
	//} BMP_CORE_HEADER;	

	float m_Spacings[3];

private:
	void (* m_ImgProgressMethod) (void* src_img,void* des_img,int MVTK_DataType,int src_w,int src_h,int& des_w,int& des_h);
//	mvtkBMPReader(const mvtkBMPReader&){};
//	void operator=(const mvtkBMPReader&){};

};

#endif

