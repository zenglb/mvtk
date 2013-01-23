#ifndef __mvtkScene_h
#define __mvtkScene_h

#include "mvtkAbstractScene.h"
#include "mvtkQuaternion.h"

class MVTK_COMMON_API mvtkScene : public mvtkAbstractScene
{
public:
	mvtkScene();
	virtual ~mvtkScene();

	void SetFovy(float fovy);

	void SetRotateRadPerPixel(float radPerPixel) { m_RadPerPixel=radPerPixel;}
	float GetRotateRadPerPixel() { return m_RadPerPixel; }

	void SetScaleRatePerPixel(float scaleRatePerPixel) { m_ScaleRatePerPixel=scaleRatePerPixel;}
	float GetScaleRatePerPixel() { return m_ScaleRatePerPixel; }

	void GetTranslate(float translate[3]);

	float GetScale() { return m_Scale;}
	const mvtkQuaternion& GetRotation() { return m_Rotation; }

	void SetTranslate(const float translate[3]);
	void SetScale(float scale);

	void SetRotation(const mvtkQuaternion& rotation);
	const mvtkMatrix4x4& GetViewMatrix();
	const mvtkMatrix4x4& GetProjectionMatrix();

	float GetZTranslateBase() { return m_ZTranslateBase;} 

	void GetViewPort(float* viewport) { viewport[0]=(float)m_ViewPort[0]; viewport[1]=(float)m_ViewPort[1];}

	float GetFovy() {return m_Fovy;}

	virtual void Render();
	virtual void Resize(int width, int height);
	
	virtual void LButtonDown(int x, int y, bool &redisplay);
	virtual void LButtonUp(int x, int y, bool &redisplay);

	virtual void MButtonDown(int x, int y, bool &redisplay);
	virtual void MButtonUp(int x, int y, bool &redisplay);

	virtual void RButtonDown(int x, int y, bool &redisplay);
	virtual void RButtonUp(int x, int y, bool &redisplay);

	virtual void MouseMove(int x, int y, bool &redisplay);

protected:
	virtual void RenderContent();
	virtual void GetSize3D(float size3D[3]);
	void SetSize3DModified();

	int m_OldMouseX,m_OldMouseY;

private:
	void _calculateCamera();
	void _calculateMatrix();
	void _makeReference();

private:
	int m_ViewPort[2];
	
// Camera Intrinsic Parameters (Input)
	float m_Fovy;

// Camera Intrinsic Parameters (Need Calculate)
	float m_Near, m_Far;

// Camera Exterior Parameter (Need Calculate)
	float m_ZTranslateBase;

// Camera Exterior Parameters (Input)
	float m_Translate[3];
	float m_Scale;
	mvtkQuaternion m_Rotation;	

// Status
	bool m_NeedCalculateCamera;
	bool m_NeedCalculateMatrix;

// Matrix
	mvtkMatrix4x4 m_ViewMatrix;
	mvtkMatrix4x4 m_ProjectionMatrix;

////// Manipulation

// Manipulation Sensitivity
	float m_RadPerPixel;
	float m_ScaleRatePerPixel;

// Parameter References
	float m_OldTranslate[3];
	float m_OldScale;
	mvtkQuaternion m_OldRotation;	

// Manipulation Status
	bool m_Rotating;
	bool m_Scaling;
	bool m_Moving;

};

#endif
