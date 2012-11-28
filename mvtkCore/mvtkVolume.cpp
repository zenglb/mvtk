#include "mvtkVolume.h"

mvtkVolume::mvtkVolume(){
	memset(this->m_Dimensions,0,4*sizeof(int));
	memset(this->m_Increments,0,4*sizeof(int));
	memset(this->m_Spacings,0,4*sizeof(int));

	this->m_DataType=0;
	this->m_NumberOfChannel=0;

	this->m_IsInitialize=false;

	this->m_Data=NULL;
}

mvtkVolume::~mvtkVolume(){
	delete this->m_Data;
}

void mvtkVolume::Initialize(){
	if(this->m_Data!=NULL){
		delete this->m_Data;
	}
	this->m_IsInitialize=false;

	unsigned long long s=((unsigned long)m_NumberOfChannel)*((unsigned long)m_Dimensions[0])*((unsigned long)m_Dimensions[1])*((unsigned long)m_Dimensions[2])*((unsigned long)m_Dimensions[3]);
	if(s>=2147483647){
		mvtkDebugMessage("Out of range.Max is 2147483647(0x7fffffff).");
		return;
	}
	switch(this->m_DataType){ 
		case MVTK_VOID:			return; 
		case MVTK_BIT:			return; 
		case MVTK_CHAR:			this->m_Data=new char[s];break; 
		case MVTK_UNSIGNED_CHAR:this->m_Data=new unsigned char[s];break; 
		case MVTK_SHORT:		this->m_Data=new short[s];break; 
		case MVTK_UNSIGNED_SHORT:this->m_Data=new unsigned short[s];break; 
		case MVTK_INT:			this->m_Data=new int[s];break; 
		case MVTK_UNSIGNED_INT:	this->m_Data=new unsigned int[s];break; 
		case MVTK_LONG:			this->m_Data=new long[s];break; 
		case MVTK_UNSIGNED_LONG:this->m_Data=new unsigned long[s];break; 
		case MVTK_FLOAT:		this->m_Data=new float[s];break; 
		case MVTK_DOUBLE:		this->m_Data=new double[s];break; 
		default:return; 
	} 
	if(this->m_Data!=NULL){
		this->m_IsInitialize=true;
	}
}

void mvtkVolume::_computeIncrements(){
	this->m_Increments[0]=this->m_NumberOfChannel; //x
	this->m_Increments[1]=this->m_Dimensions[0]*this->m_Increments[0]; //y
	this->m_Increments[2]=this->m_Dimensions[1]*this->m_Increments[1]; //t
	this->m_Increments[3]=this->m_Dimensions[2]*this->m_Increments[2]; //t
}

//这个方法效率比较低 别这样用 最好使用getData 获取数据自己实现
double mvtkVolume::GetData(int x, int y, int z,int t, int c,bool check_bounds){
	double ret=0;

	if(check_bounds&&x>=this->m_Dimensions[0]&&y>=this->m_Dimensions[1]&&z>=this->m_Dimensions[2]&&t>=this->m_Dimensions[3]){
		return ret;
	}

	long s=c+x*this->m_NumberOfChannel+y*this->m_Increments[0]+z*this->m_Increments[1]+t*this->m_Increments[2];

	switch(this->m_DataType){ 
		case MVTK_CHAR:			ret=(double)((char*)this->m_Data)[s];break; 
		case MVTK_UNSIGNED_CHAR:ret=(double)((unsigned char*)this->m_Data)[s];break; 
		case MVTK_SHORT:		ret=(double)((short*)this->m_Data)[s];break; 
		case MVTK_UNSIGNED_SHORT:ret=(double)((unsigned short*)this->m_Data)[s];break; 
		case MVTK_INT:			ret=(double)((int*)this->m_Data)[s];break; 
		case MVTK_UNSIGNED_INT:	ret=(double)((unsigned int*)this->m_Data)[s];break; 
		case MVTK_LONG:			ret=(double)((long*)this->m_Data)[s];break; 
		case MVTK_UNSIGNED_LONG:ret=(double)((unsigned long*)this->m_Data)[s];break; 
		case MVTK_FLOAT:		ret=(double)((float*)this->m_Data)[s];break; 
		case MVTK_DOUBLE:		ret=(double)((double*)this->m_Data)[s];break; 
	} 
	return ret;
}