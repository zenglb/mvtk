#include "mvtkVolume.h"
#include "mvtkVector4.h"

class VolumeAccess
{
public:
	VolumeAccess(){}
	virtual ~VolumeAccess(){}
	virtual float GetScalarValue(int x,int y,int z)=0;
	virtual float GetScalarValue(mvtkVector4 pos)=0;
	virtual mvtkVector4 GetNormal(mvtkVector4 pos)=0;
};

template <typename T>
class T_VolumeAccess : public VolumeAccess
{
private:
	T* m_data;
	int m_dims[3];
	float m_spacings[3];
	int m_incs[3];
public:	
	T_VolumeAccess(void* data,const int* dims,const float* spacings)
	{
		m_data=(T*)data;
		m_dims[0]=dims[0];m_dims[1]=dims[1];m_dims[2]=dims[2];
		m_spacings[0]=spacings[0];m_spacings[1]=spacings[1];m_spacings[2]=spacings[2];

		m_incs[0]=1;
		m_incs[1]=m_dims[0];
		m_incs[2]=m_dims[0]*m_dims[1];

	}
	virtual ~T_VolumeAccess(){}

	virtual float GetScalarValue(int x,int y,int z)
	{
		return (float)m_data[x+(y+z*m_dims[1])*m_dims[0]];
	}
	
	virtual float GetScalarValue(mvtkVector4 pos)
	{
		if (pos[0]<0 || pos[0]>=m_dims[0]-1 || pos[1]<0 || pos[1]>=m_dims[1]-1 || pos[2]<0 || pos[2]>=m_dims[2]-1) return 0.0f;

		float a,b,c,d;
		int ipos[3];
		float fpos1,fpos2;

		T* ptr=m_data;

		ipos[0]=(int)pos[0]; ipos[1]=(int)pos[1]; ipos[2]=(int)pos[2];
		ptr+=ipos[0]+ipos[1]*m_incs[1]+ipos[2]*m_incs[2];

		fpos2=pos[0]-ipos[0];
		fpos1=1.0f-fpos2;
		
		a=ptr[0]*fpos1+ptr[1]*fpos2;
		b=ptr[m_incs[1]]*fpos1+ptr[m_incs[1]+1]*fpos2;
		c=ptr[m_incs[2]]*fpos1+ptr[m_incs[2]+1]*fpos2;
		d=ptr[m_incs[1]+m_incs[2]]*fpos1+ptr[m_incs[1]+m_incs[2]+1]*fpos2;	

		fpos2=pos[1]-ipos[1];
		fpos1=1.0f-fpos2;

		a=a*fpos1+b*fpos2;
		c=c*fpos1+d*fpos2;

		fpos2=pos[2]-ipos[2];
		fpos1=1.0f-fpos2;

		return a*fpos1+c*fpos2;
	}

	virtual mvtkVector4 GetNormal(mvtkVector4 pos)
	{
		mvtkVector4 curPos;
		mvtkVector4 sample1,sample2;

		curPos=pos;
		curPos[0]-=1.0f;
		sample1[0]=this->GetScalarValue(curPos);
		curPos=pos;
		curPos[0]+=1.0f;
		sample2[0]=this->GetScalarValue(curPos);

		curPos=pos;
		curPos[1]-=1.0f;
		sample1[1]=this->GetScalarValue(curPos);
		curPos=pos;
		curPos[1]+=1.0f;
		sample2[1]=this->GetScalarValue(curPos);

		curPos=pos;
		curPos[2]-=1.0f;
		sample1[2]=this->GetScalarValue(curPos);
		curPos=pos;
		curPos[2]+=1.0f;
		sample2[2]=this->GetScalarValue(curPos);
		
		sample1[3]=0.0;
		sample2[3]=0.0;

		sample2=sample2-sample1;
		sample2[0]/=m_spacings[0];
		sample2[1]/=m_spacings[1];
		sample2[2]/=m_spacings[2];

		sample2.Normalize();

		return sample2;
	}

};

static VolumeAccess *va;

static inline float GetScalarValue(int x,int y,int z)
{
	if (va) return va->GetScalarValue(x,y,z); else return 0.0f;
}

static inline float GetScalarValue(mvtkVector4 pos)
{
	if (va) return va->GetScalarValue(pos); else return 0.0f;
}

static inline mvtkVector4 GetNormal(mvtkVector4 pos)
{
	if (va) return va->GetNormal(pos); else return mvtkVector4();
}

static bool SingleScalarVolumePrepare(mvtkVolume *volume)
{
	if (!volume) return false;

	va=0;

	void *data;
	int dims[4];
	float spacings[4];
	data=volume->GetData();
	volume->GetDimensions(dims);
	volume->GetSpacings(spacings);

	switch(volume->GetDataType()){
		case MVTK_CHAR:			va=new T_VolumeAccess<char>(data,dims,spacings);break; 
		case MVTK_UNSIGNED_CHAR:va=new T_VolumeAccess<unsigned char>(data,dims,spacings);break;
		case MVTK_SHORT:		va=new T_VolumeAccess<short>(data,dims,spacings);break;
		case MVTK_UNSIGNED_SHORT:va=new T_VolumeAccess<unsigned short>(data,dims,spacings);break;
		case MVTK_INT:			va=new T_VolumeAccess<int>(data,dims,spacings);break;
		case MVTK_UNSIGNED_INT:	va=new T_VolumeAccess<unsigned int>(data,dims,spacings);
		case MVTK_LONG:			va=new T_VolumeAccess<long>(data,dims,spacings);break;
		case MVTK_UNSIGNED_LONG:va=new T_VolumeAccess<unsigned long>(data,dims,spacings);break;
		case MVTK_FLOAT:		va=new T_VolumeAccess<float>(data,dims,spacings);break;
		case MVTK_DOUBLE:		va=new T_VolumeAccess<double>(data,dims,spacings);break;
	}
	if(va!=NULL) return true; else return false;
}

static void SingleScalarVolumeClear()
{
	if (va) delete va;
}