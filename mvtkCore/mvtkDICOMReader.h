#ifndef __mvtkDICOMReader_H
#define __mvtkDICOMReader_H




#include "mvtkVolumeReader.h"
#include "mvtkVolume.h"

class DICOMParser;
class DICOMAppHelper;
class MVTK_COMMON_API mvtkDICOMReader:public mvtkVolumeReader
{
public:
	MVTK_TYPE(mvtkDICOMReader,mvtkVolumeReader)
	virtual void Update();
protected:
	mvtkDICOMReader(void);
	~mvtkDICOMReader(void);
private:
	
	int CanReadFile(const char* fname);
	DICOMParser* Parser;
	DICOMAppHelper* AppHelper;
};

#endif