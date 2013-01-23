#include "mvtkIsosurfaceRayCaster.h"

mvtkIsosurfaceRayCaster::mvtkIsosurfaceRayCaster()
{
	m_LightDirection[0] = 1.0f;
	m_LightDirection[1] = 0.0f;
	m_LightDirection[2] = 0.0f;
	m_LightDirection[3] = 0.0f;
	m_LightIntensity = 1.0f;
	m_LightColor[0] = 1.0f;
	m_LightColor[1] = 1.0f;
	m_LightColor[2] = 1.0f;  

	m_Ambient = 0.1f; 
	m_Diffuse = 0.7f;
	m_Specular = 0.2f;
	m_SpecularPower = 10.0f;

	m_SampleDistance = 1.0f;	
	m_Isovalue=100.0f;
	m_SurfaceColor[0]=1.0f;
	m_SurfaceColor[1]=1.0f;
	m_SurfaceColor[2]=1.0f;

}
mvtkIsosurfaceRayCaster::~mvtkIsosurfaceRayCaster()
{

}
void mvtkIsosurfaceRayCaster::SetSurfaceColor(float r,float g,float b)
{
	m_SurfaceColor[0]=r;
	m_SurfaceColor[1]=g;
	m_SurfaceColor[2]=b;
}
void mvtkIsosurfaceRayCaster::GetSurfaceColor(float &r,float &g,float &b)
{
	r=m_SurfaceColor[0];
	g=m_SurfaceColor[1];
	b=m_SurfaceColor[2];
}

void mvtkIsosurfaceRayCaster::SetLightDirection(float x,float y,float z)
{
	float l=sqrtf(x*x+y*y+z*z);
	if (l==0)
	{
		m_LightDirection[0] = 1.0f;
		m_LightDirection[1] = 0.0f;
		m_LightDirection[2] = 0.0f;
		m_LightDirection[3] = 0.0f;
	}
	else
	{
		x/=l; y/=l; z/=l;
		m_LightDirection[0]=x;m_LightDirection[1]=y;m_LightDirection[2]=z;
		m_LightDirection[3] = 0.0f;
	}
}
void mvtkIsosurfaceRayCaster::GetLightDirection(float &x,float &y,float &z)
{
	x=m_LightDirection[0];
	y=m_LightDirection[1];
	z=m_LightDirection[2];
}
void mvtkIsosurfaceRayCaster::SetLightColor(float r,float g, float b)
{
	m_LightColor[0]=r; m_LightColor[1]=g; m_LightColor[2]=b;
}
void mvtkIsosurfaceRayCaster::GetLightColor(float &r,float &g, float &b)
{
	r=m_LightColor[0]; g=m_LightColor[1]; b=m_LightColor[2];
}

void mvtkIsosurfaceRayCaster::MakeReference()
{
	m_OldLightDirection=m_LightDirection;
}

void mvtkIsosurfaceRayCaster::RotateLightDirection(const mvtkMatrix4x4& matrix)
{
	m_LightDirection=matrix*m_OldLightDirection;
}
