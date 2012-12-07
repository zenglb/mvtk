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

	virtual void Update();

	mvtkBMPReader(){};
	virtual ~mvtkBMPReader(){}; 

//protected:
//	mvtkBMPReader(){};
//	virtual ~mvtkBMPReader(){};    

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

	

private:
	
//	mvtkBMPReader(const mvtkBMPReader&){};
//	void operator=(const mvtkBMPReader&){};

};

#endif

