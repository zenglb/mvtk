#include "mvtkTypicalRayProducer.h"


static inline mvtkVector4 CastRay(const mvtkVector4& voxel_zero,const mvtkVector4& voxel_unit,const mvtkVector4& CameraDirection,float tnear,float tfar);

static mvtkMatrix4x4 P2MMatrix; 
static mvtkMatrix4x4 M2VMatrix; 
static int Volume_Dims[3];

static mvtkVector4 EyePos;

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

static inline void ProduceRay(float pixX,float pixY, mvtkVector4& voxel_zero,mvtkVector4& voxel_unit, mvtkVector4& CameraDirection, float& tnear, float& tfar)
{
	mvtkVector4 model_pix=P2MMatrix*mvtkVector4(pixX,pixY,0.0f);
	model_pix*=1.0f/model_pix[3];

	CameraDirection=model_pix-EyePos;
	CameraDirection.Normalize();

	voxel_zero=M2VMatrix*EyePos;
	voxel_unit=M2VMatrix*CameraDirection;

	/// Find Start Point
	float t1,t2;

	t1=-voxel_zero[0]/voxel_unit[0];
	t2=(Volume_Dims[0]-1.0f-voxel_zero[0])/voxel_unit[0];

	float tminX=min(t1,t2);
	float tmaxX=max(t1,t2);

	t1=-voxel_zero[1]/voxel_unit[1];
	t2=(Volume_Dims[1]-1.0f-voxel_zero[1])/voxel_unit[1];
	
	float tminY=min(t1,t2);
	float tmaxY=max(t1,t2);

	t1=-voxel_zero[2]/voxel_unit[2];
	t2=(Volume_Dims[2]-1.0f-voxel_zero[2])/voxel_unit[2];

	float tminZ=min(t1,t2);
	float tmaxZ=max(t1,t2);

	tnear=max(max(tminX, tminY), max(tminX, tminZ));
	tnear=max(tnear,0.0f);
	tfar=min(min(tmaxX,tmaxY),min(tmaxX,tmaxZ));


}

#include "mvtkSPMD.h"

void GenerateImage_MT(int NumberOfThreads, int ThreadID,void* userData)
{
	mvtkTypicalRayProducer *RayProducer=(mvtkTypicalRayProducer *)userData;

	int imageSize[2];
	int imageOrigin[2];

	RayProducer->GetImageInUseSize(imageSize);
	RayProducer->GetImageOrigin(imageOrigin);
	float* image=RayProducer->GetImageData();
	if (!image) return;

	int i,j;
	for (j=imageOrigin[1];j<imageOrigin[1]+imageSize[1];j++)
	{
		for (i=imageOrigin[0]+ThreadID;i<imageOrigin[0]+imageSize[0];i+=NumberOfThreads)
		{
			mvtkVector4 voxel_zero, voxel_unit, CameraDirection;
			float tnear,tfar;
			ProduceRay(i+0.5f,j+0.5f,voxel_zero,voxel_unit,CameraDirection,tnear,tfar);
			mvtkVector4 value(0.0f,0.0f,0.0f,0.0f);
			if (tnear<tfar) value= CastRay(voxel_zero,voxel_unit,CameraDirection,tnear,tfar);
			float *pImage=image+(i-imageOrigin[0]+(j-imageOrigin[1])*imageSize[0])*4;
			pImage[0]=max(min(value[0],1.0f),0.0f);
			pImage[1]=max(min(value[1],1.0f),0.0f);
			pImage[2]=max(min(value[2],1.0f),0.0f);
			pImage[3]=max(min(value[3],1.0f),0.0f);
		}
	}
}

static inline void GenerateImage(mvtkTypicalRayProducer *RayProducer)
{
	if (!RayProducer) return;
	RayProducer->UpdateMatrixAndBounds();
	P2MMatrix=RayProducer->GetPixelsToModelMatrix();
	M2VMatrix=RayProducer->GetModelToVolumeMatrix();
	float Volume_Spacings[3];
	RayProducer->GetVolSize(Volume_Dims,Volume_Spacings);

	EyePos[0]=P2MMatrix[8]/P2MMatrix[11];
	EyePos[1]=P2MMatrix[9]/P2MMatrix[11];
	EyePos[2]=P2MMatrix[10]/P2MMatrix[11];
	EyePos[3]=1.0f;

	LaunchSPMD(GenerateImage_MT,RayProducer);
}
