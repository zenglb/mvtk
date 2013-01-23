#include "mvtkIsosurfaceVRScene.h"
#include "mvtkIsosurfaceRayCaster.h"
#include "mvtkTypicalRayProducer.h"
#include "mvtkVolume.h"

#include "GL/glew.h"

mvtkIsosurfaceVRScene::mvtkIsosurfaceVRScene()
{
	m_Data=NULL;
	m_BackgroundColor[0]=m_BackgroundColor[1]=m_BackgroundColor[2]=0.0f;

	m_RayCaster=new mvtkIsosurfaceRayCaster;
	m_RayProducer=new mvtkTypicalRayProducer;
}

mvtkIsosurfaceVRScene::~mvtkIsosurfaceVRScene()
{
	delete m_RayProducer;
	delete m_RayCaster;
}

void mvtkIsosurfaceVRScene::SetData(mvtkVolume *data)
{
	m_Data=data;
	SetSize3DModified();

	if (!data) return;
	
	int dims[4];
	float spacings[4];
	m_Data->GetDimensions(dims);
	m_Data->GetSpacings(spacings);

	m_RayProducer->SetVolSize(dims,spacings);
	m_RayCaster->SetSampleDistance(sqrt((spacings[0]*spacings[0]+spacings[1]*spacings[1]+spacings[2]*spacings[2]))/3);

	double minValue,maxValue;
	data->GetMinMaxValue(minValue,maxValue);
	m_RayCaster->SetIsovalue((float)(maxValue+minValue)*0.5f);

}

void mvtkIsosurfaceVRScene::SetBackGroundColor(float r,float g, float b)
{
	m_BackgroundColor[0]=r; m_BackgroundColor[1]=g; m_BackgroundColor[2]=b;
}

void mvtkIsosurfaceVRScene::GetBackGroundColor(float& r,float& g, float& b)
{
	r=m_BackgroundColor[0]; g=m_BackgroundColor[1]; b=m_BackgroundColor[2];
}

void mvtkIsosurfaceVRScene::SetIsovalue(float isovalue)
{
	m_RayCaster->SetIsovalue(isovalue);
}
float mvtkIsosurfaceVRScene::GetIsovalue()
{
	return m_RayCaster->GetIsovalue();
}
void mvtkIsosurfaceVRScene::SetSurfaceColor(float r,float g,float b)
{
	m_RayCaster->SetSurfaceColor(r,g,b);
}
void mvtkIsosurfaceVRScene::GetSurfaceColor(float &r,float &g,float &b)
{
	m_RayCaster->GetSurfaceColor(r,g,b);
}

void mvtkIsosurfaceVRScene::SetLightDirection(float x,float y,float z)
{
	m_RayCaster->SetLightDirection(x,y,z);
}
void mvtkIsosurfaceVRScene::SetLightIntensity(float intensity)
{
	m_RayCaster->SetLightIntensity(intensity);
}
void mvtkIsosurfaceVRScene::SetLightColor(float r,float g,float b)
{
	m_RayCaster->SetLightColor(r,g,b);
}
void mvtkIsosurfaceVRScene::SetAmbient(float value)
{
	m_RayCaster->SetAmbient(value);
}
float mvtkIsosurfaceVRScene::GetAmbient()
{
	return m_RayCaster->GetAmbient();
}
void mvtkIsosurfaceVRScene::SetDiffuse(float value)
{
	m_RayCaster->SetDiffuse(value);
}
float mvtkIsosurfaceVRScene::GetDiffuse()
{
	return m_RayCaster->GetDiffuse();
}
void mvtkIsosurfaceVRScene::SetSpecular(float value)
{
	m_RayCaster->SetSpecular(value);
}
float mvtkIsosurfaceVRScene::GetSpecular()
{
	return m_RayCaster->GetSpecular();
}
void mvtkIsosurfaceVRScene::SetSpecularPower(float value)
{
	m_RayCaster->SetSpecularPower(value);
}
float mvtkIsosurfaceVRScene::GetSpecularPower()
{
	return m_RayCaster->GetSpecularPower();
}

void mvtkIsosurfaceVRScene::Init()
{
	glewInit();
}

void mvtkIsosurfaceVRScene::Resize(int width, int height)
{
	mvtkScene::Resize(width,height);
	m_RayProducer->SetViewPort(width,height);
}

void  mvtkIsosurfaceVRScene::SetSampleDistance(float sd)
{
	m_RayCaster->SetSampleDistance(sd);
}
float mvtkIsosurfaceVRScene::GetSampleDistance()
{
	return m_RayCaster->GetSampleDistance();
}

void mvtkIsosurfaceVRScene::RenderContent()
{
	glClearColor(m_BackgroundColor[0], m_BackgroundColor[1], m_BackgroundColor[2], 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_RayProducer->SetViewMatrix(this->GetViewMatrix());
	m_RayProducer->SetProjectionMatrix(this->GetProjectionMatrix());

	mvtkMatrix4x4 ivm=this->GetViewMatrix(); ivm.Inverse();
	m_RayCaster->SetLightDirection(-ivm[8],-ivm[9],-ivm[10]);

	if (_renderCore())	m_RayProducer->RenderImage();

}

void mvtkIsosurfaceVRScene::GetSize3D(float size[3])
{
	int dims[4];
	float spacings[4];
	if (m_Data) 
	{
		m_Data->GetDimensions(dims);
		m_Data->GetSpacings(spacings);
	}

	size[0]=dims[0]*spacings[0];
	size[1]=dims[1]*spacings[1];
	size[2]=dims[2]*spacings[2];
}

#include "mvtkSingleScalarVolume.core.h"
#include "mvtkIsosurfaceRayCaster.core.h"
#include "mvtkTypicalRayProducer.core.h"

bool mvtkIsosurfaceVRScene::_renderCore()
{
	if (!SingleScalarVolumePrepare(m_Data)) return false;
	if (!IsosurfaceRayCasterPrepare(m_RayCaster)) return false;
	GenerateImage(m_RayProducer);
	SingleScalarVolumeClear();
	return true;
}


