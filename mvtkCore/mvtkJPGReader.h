#ifndef __mvtkJPGReader_h
#define __mvtkJPGReader_h

#include "mvtkVolumeReader.h"

class MVTK_COMMON_API mvtkJPGReader: public mvtkVolumeReader
{
public:
	MVTK_TYPE(mvtkJPGReader,mvtkVolumeReader)
	virtual void Update();
protected:
	mvtkJPGReader(void);
	~mvtkJPGReader(void);
private:
	

};

#endif