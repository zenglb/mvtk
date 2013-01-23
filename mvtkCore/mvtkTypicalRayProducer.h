#ifndef __mvtkTypicalRayProducer_h
#define __mvtkTypicalRayProducer_h

#include "mvtkMatrix4x4.h"

class mvtkTypicalRayProducer
{
public:
	mvtkTypicalRayProducer();
	virtual ~mvtkTypicalRayProducer();

	void SetViewPort(int width,int height);	
	void SetVolSize(const int volDims[3],const float volSpacings[3]);
	void GetVolSize(int volDims[3], float volSpacings[3]);

	void SetViewMatrix(const mvtkMatrix4x4& ViewMatrix);
	void SetProjectionMatrix(const mvtkMatrix4x4& ProjectionMatrix);

	void UpdateMatrixAndBounds();

	const mvtkMatrix4x4& GetPixelsToModelMatrix() {return m_PixelsToModelMatrix;}
	const mvtkMatrix4x4& GetModelToVolumeMatrix() {return m_ModelToVolumeMatrix;}
	
	void GetImageInUseSize(int imageSize[2]);
	void GetImageOrigin(int imageOrigin[2]);

	float *GetImageData() { return m_ImageData; }

	void RenderImage();

private:
	void _calculateMatrix();
	bool _calculateBounds();

	int m_ViewPort[2];
	int m_VolDims[3];
	float m_VolSpacings[3];
	float m_VolSize[3];

	mvtkMatrix4x4 m_ViewMatrix;
	mvtkMatrix4x4 m_ProjectionMatrix;

	mvtkMatrix4x4 m_PixelsToModelMatrix;
	mvtkMatrix4x4 m_ModelToPixelsMatrix;

	mvtkMatrix4x4 m_ModelToVolumeMatrix;	 
	mvtkMatrix4x4 m_PixelsToViewMatrix;

	mvtkVector4 m_CameraPos;

	int m_ImageInUseSize[2];
	int m_ImageOrigin[2];

	float *m_ImageData;

};

#endif 
