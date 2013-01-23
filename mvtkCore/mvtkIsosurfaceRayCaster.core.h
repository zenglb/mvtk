#include "mvtkIsosurfaceRayCaster.h"
#include "mvtkVector4.h"
#include "mvtkVector3.h"
static inline float GetScalarValue(mvtkVector4 pos);
static inline mvtkVector4 GetNormal(mvtkVector4 pos);

static float sampleDistance;
static float isovalue;
static mvtkVector4 baseColor;
static mvtkVector3 ambient;
static mvtkVector3 diffuse;
static mvtkVector3 specular;
static float specular_power;
static mvtkVector4 light_direction;
static float spec_threshold;


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


static inline mvtkVector4 GetColor(const mvtkVector4& pos,const mvtkVector4& CameraDirection,bool increasing)
{
	float n_dot_l;
	float n_dot_h;
	mvtkVector4 normal=GetNormal(pos);
	mvtkVector3 k=ambient;
	mvtkVector3 b;
	n_dot_l=normal*light_direction;
	if ((n_dot_l>0.0f && increasing) || (n_dot_l<0.0f && !increasing))
    {
		n_dot_l=n_dot_l>0?n_dot_l:-n_dot_l;
        k+=diffuse*n_dot_l;
		mvtkVector4 HalfwayVector=light_direction+CameraDirection;
		HalfwayVector.Normalize();
        n_dot_h=normal*HalfwayVector;
		if (n_dot_h<0) n_dot_h=-n_dot_h;
        if (n_dot_h > spec_threshold)
        {
            b=specular*powf(n_dot_h,specular_power);
        }
	}
	mvtkVector4 result=baseColor;
	result[0]=k[0]*result[0]+b[0];
	result[1]=k[1]*result[1]+b[1];
	result[2]=k[2]*result[2]+b[2];
	return result;
}

static inline mvtkVector4 CastRay(const mvtkVector4& voxel_zero,const mvtkVector4& voxel_unit,const mvtkVector4& CameraDirection,float tnear,float tfar)
{
	float t=tnear;
	mvtkVector4 pos=voxel_zero + voxel_unit * t;
	mvtkVector4 voxel_step=voxel_unit*sampleDistance;

	float scalar1=GetScalarValue(pos);
	mvtkVector4 pos1=pos;
	t += sampleDistance;
	pos += voxel_step;
	while(t<tfar)
    {
		float scalar=GetScalarValue(pos);
		if ((scalar>=isovalue && scalar1<=isovalue) || (scalar<=isovalue && scalar1>=isovalue))
		{
			mvtkVector4 isoPos=(isovalue-scalar1)/(scalar-scalar1)*(pos-pos1)+pos1;
			return GetColor(isoPos,CameraDirection,scalar1<=isovalue);
		}
		scalar1=scalar;
		pos1=pos;
		t += sampleDistance;
		pos += voxel_step;
    }
	return mvtkVector4(0.0f,0.0f,0.0f,0.0f);	

}

static bool IsosurfaceRayCasterPrepare(mvtkIsosurfaceRayCaster *RayCaster)
{
	if (!RayCaster) return false;

	sampleDistance=RayCaster->GetSampleDistance();
	isovalue=RayCaster->GetIsovalue();

	RayCaster->GetSurfaceColor(baseColor[0],baseColor[1],baseColor[2]);
	baseColor[3]=1.0f;
	
	float lightColor[3];
	RayCaster->GetLightColor(lightColor[0],lightColor[1],lightColor[2]);
	float LightIntensity=RayCaster->GetLightIntensity();

	lightColor[0]*=LightIntensity;
	lightColor[1]*=LightIntensity;
	lightColor[2]*=LightIntensity;

	float f_ambient=RayCaster->GetAmbient();

	ambient[0]=f_ambient*lightColor[0];
	ambient[1]=f_ambient*lightColor[1];
	ambient[2]=f_ambient*lightColor[2];

	float f_diffuse=RayCaster->GetDiffuse();

	diffuse[0]=f_diffuse*lightColor[0];
	diffuse[1]=f_diffuse*lightColor[1];
	diffuse[2]=f_diffuse*lightColor[2];

	float f_specular=RayCaster->GetSpecular();

	specular[0]=f_specular*lightColor[0];
	specular[1]=f_specular*lightColor[1];
	specular[2]=f_specular*lightColor[2];

	specular_power=RayCaster->GetSpecularPower();

	spec_threshold=powf(0.001f/max(max(specular[0],specular[1]),specular[2]),1.0f/specular_power);

	RayCaster->GetLightDirection(light_direction[0],light_direction[1],light_direction[2]);
	light_direction[3]=0.0f;

	return true;
}
