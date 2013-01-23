#ifndef __mvtkVolumeContourFilter_h
#define __mvtkVolumeContourFilter_h

#include "mvtkVolumeToVolumeFilter.h"
#include "mvtkVolume.h"

class MVTK_COMMON_API mvtkVolumeContourFilter : public mvtkVolumeToVolumeFilter
{
public:
	MVTK_TYPE(mvtkVolumeContourFilter,mvtkVolumeToVolumeFilter)
	virtual void PrintSelf(ostream& os){};  

	UPDATE_FUNCTION_MACRO

protected:
	virtual ~mvtkVolumeContourFilter(){};
	mvtkVolumeContourFilter(){};

private:
	template <typename T>
	void _execute(T *data_ptr,mvtkVolume* in_data);

	template <typename T>
	void _internalVoxelClassify(T *data_ptr, int dimension[3], int *InternalVoxel);
	//	mvtkVolumeToVolumeFilter(const mvtkVolumeToVolumeFilter&);
	//	void operator=(const mvtkVolumeToVolumeFilter&);

};


//#define DEFINED_mvtkVolumeToVolumeFilter


#endif


