#ifndef __mvtkIsosurfaceRayCaster_h
#define __mvtkIsosurfaceRayCaster_h

#include "mvtkMatrix4x4.h"

class mvtkIsosurfaceRayCaster
{
public:
	mvtkIsosurfaceRayCaster();
	virtual ~mvtkIsosurfaceRayCaster();

	void  SetSampleDistance(float sd) {m_SampleDistance = sd;} 
	float GetSampleDistance() { return m_SampleDistance;}

	void SetIsovalue(float isovalue) {m_Isovalue=isovalue;}
	float GetIsovalue() { return m_Isovalue;}

	void SetSurfaceColor(float r,float g,float b);
	void GetSurfaceColor(float &r,float &g,float &b);

	void SetLightDirection(float x,float y,float z);
	void GetLightDirection(float &x,float &y,float &z);
	void SetLightIntensity(float intensity){m_LightIntensity=intensity;}
	float GetLightIntensity() {return m_LightIntensity;}
	void SetLightColor(float r,float g,float b);
	void GetLightColor(float &r,float &g, float &b);

	void SetAmbient(float value) { m_Ambient = value; }
	float GetAmbient() { return m_Ambient; }

	void SetDiffuse(float value) { m_Diffuse = value; }
	float GetDiffuse() { return m_Diffuse; }

	void SetSpecular(float value) { m_Specular = value; }
	float GetSpecular() { return m_Specular; }

	void SetSpecularPower(float value) 	{ m_SpecularPower = value; }
	float GetSpecularPower() { return m_SpecularPower; }  

	void MakeReference();
	void RotateLightDirection(const mvtkMatrix4x4& matrix);

private:
	float m_Isovalue;
	float m_SurfaceColor[3];
	mvtkVector4 m_LightDirection;
	mvtkVector4 m_OldLightDirection;
	float m_LightIntensity;
	float m_LightColor[3];

	float m_Ambient;
	float m_Diffuse;
	float m_Specular;
	float m_SpecularPower;

	float m_SampleDistance;

};


#endif
