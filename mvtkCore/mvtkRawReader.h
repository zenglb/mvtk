#ifndef __mvtkRawReader_H
#define __mvtkRawReader_H

#include "mvtkVolumeReader.h"

class MVTK_COMMON_API mvtkRawReader: public mvtkVolumeReader
{
public:
	MVTK_TYPE(mvtkRawReader,mvtkVolumeReader)
	virtual void Update();
	void SetWidth(int w);
	void SetHeight(int h);
protected:
	mvtkRawReader(void);
	~mvtkRawReader(void);
	int w;
	int h;
};

#endif