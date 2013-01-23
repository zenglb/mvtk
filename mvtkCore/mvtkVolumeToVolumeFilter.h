#ifndef __mvtkVolumeToVolumeFilter_h
#define __mvtkVolumeToVolumeFilter_h

#define UPDATE_FUNCTION_MACRO  \
	virtual void Update(){ \
		if(this->m_StartMethod!=NULL){ \
			this->m_StartMethod(); \
		} \
 \
		if(this->m_InData==NULL){ \
			mvtkDebugMessage("Invalid input data"); \
			return; \
		} \
 \
		this->m_OutData->DeepCopy(this->m_InData,true); \
 \
		switch (this->m_OutData->GetDataType()){ \
					case MVTK_VOID:			mvtkDebugMessage("Invalid type of MVTK_VOID"); return;   \
					case MVTK_BIT:			mvtkDebugMessage("Invalid type of MVTK_BIT"); return;  \
					case MVTK_CHAR:			this->_execute((char*) this->m_OutData->GetData(),this->m_OutData);break;  \
					case MVTK_UNSIGNED_CHAR:this->_execute((unsigned char*) this->m_OutData->GetData(),this->m_OutData);break;  \
					case MVTK_SHORT:		this->_execute((short*) this->m_OutData->GetData(),this->m_OutData);break;  \
					case MVTK_UNSIGNED_SHORT:this->_execute((unsigned short*) this->m_OutData->GetData(),this->m_OutData);break;  \
					case MVTK_INT:			this->_execute((int*) this->m_OutData->GetData(),this->m_OutData);break;  \
					case MVTK_UNSIGNED_INT:	this->_execute((unsigned int*) this->m_OutData->GetData(),this->m_OutData);break;  \
					case MVTK_LONG:			this->_execute((long*) this->m_OutData->GetData(),this->m_OutData);break;  \
					case MVTK_UNSIGNED_LONG:this->_execute((unsigned long*) this->m_OutData->GetData(),this->m_OutData);break;  \
					case MVTK_FLOAT:		this->_execute((float*) this->m_OutData->GetData(),this->m_OutData);break;  \
					case MVTK_DOUBLE:		this->_execute((double*) this->m_OutData->GetData(),this->m_OutData);break;  \
					default: mvtkDebugMessage("Invalid type");return;  \
		} \
 \
		if(this->m_EndMethod!=NULL){ \
			this->m_EndMethod(); \
		} \
	}


#include "mvtkFilter.h"
#include "mvtkVolume.h"
//#include "mvtkRCPtr.h"
//#include "mvtkOoCGlobalSettings.h"

/// mvtkVolumeToVolumeFilter - abstract class specifies interface for volume to volume filter
///////////////////////////////////////////////////////////////////////////
/// mvtkVolumeToVolumeFilter is an abstract class specifies interface for
/// volume to volume filter. This type of filter has a volume input and 
/// generates a volume as output.

class MVTK_COMMON_API mvtkVolumeToVolumeFilter : public mvtkFilter
{
public:
	MVTK_ABSTRACT_TYPE(mvtkVolumeToVolumeFilter,mvtkFilter)

	virtual void PrintSelf(ostream& os){};  

	///////////////////////////////////////////////////////////////////////////
	/// Set the input volume
	/// \param inData Specify the input volume
	///////////////////////////////////////////////////////////////////////////
	void SetInput(mvtkVolume *inData) {m_InData = inData;}

	///////////////////////////////////////////////////////////////////////////
	/// Get the input volume
	/// \return Return the input volume
	///////////////////////////////////////////////////////////////////////////
	mvtkVolume* GetInput() {return m_InData;}

	///////////////////////////////////////////////////////////////////////////
	/// Get the output volume
	/// \return Return the output volume
	///////////////////////////////////////////////////////////////////////////
	mvtkVolume* GetOutput(){return m_InData;}

	virtual void Update()=0;

protected:
	mvtkVolumeToVolumeFilter(){
		this->m_OutData=mvtkVolume::New();
	}
	//没有初始化就删除 一般忽略这种情况
	virtual ~mvtkVolumeToVolumeFilter(){
		if(this->m_OutData!=NULL && !this->m_OutData->GetIsInitialize()){
			this->m_OutData->Delete();
		}
	}

	//mvtkRCPtr<mvtkVolume> m_InData;
	mvtkVolume *m_InData;
	mvtkVolume *m_OutData;

//private:
//	mvtkVolumeToVolumeFilter(const mvtkVolumeToVolumeFilter&);
//	void operator=(const mvtkVolumeToVolumeFilter&);

};


//#define DEFINED_mvtkVolumeToVolumeFilter


#endif


