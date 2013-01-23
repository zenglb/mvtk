#ifndef __mvtkIsosurfaceVRScene_h
#define __mvtkIsosurfaceVRScene_h

#include "mvtkScene.h"

class mvtkVolume;
class mvtkIsosurfaceRayCaster;
class mvtkTypicalRayProducer;

class MVTK_COMMON_API mvtkIsosurfaceVRScene : public mvtkScene
{
public:
	mvtkIsosurfaceVRScene();
	virtual ~mvtkIsosurfaceVRScene();

	void SetData(mvtkVolume *data);

	void SetBackGroundColor(float r,float g, float b);
	void GetBackGroundColor(float& r,float& g,float& b);
	
	void SetIsovalue(float isovalue);
	float GetIsovalue();

	void SetSurfaceColor(float r,float g,float b);
	void GetSurfaceColor(float &r,float &g,float &b);

	void SetLightDirection(float x,float y,float z);
	void SetLightIntensity(float intensity);
	void SetLightColor(float r,float g,float b);

	void SetAmbient(float value);
	float GetAmbient();

	void SetDiffuse(float value);
	float GetDiffuse();

	void SetSpecular(float value);
	float GetSpecular();

	void SetSpecularPower(float value);
	float GetSpecularPower();

	void  SetSampleDistance(float sd);
	float GetSampleDistance();

	virtual void Init();
	virtual void Resize(int width, int height);
	
protected:
	virtual void RenderContent();
	virtual void GetSize3D(float size[3]);

private:
	bool _renderCore();

	mvtkVolume* m_Data;
	mvtkIsosurfaceRayCaster* m_RayCaster;
	mvtkTypicalRayProducer* m_RayProducer;

	float m_BackgroundColor[3];

};

#endif
