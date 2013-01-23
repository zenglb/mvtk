#include "mvtkTypicalRayProducer.h"
#include "GL/glew.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

mvtkTypicalRayProducer::mvtkTypicalRayProducer()
{
	m_ImageInUseSize[0]      = 0;
    m_ImageInUseSize[1]      = 0;
	m_VolSize[0]=m_VolSize[1]=m_VolSize[2]=0;
	m_ImageData=0;
}

mvtkTypicalRayProducer::~mvtkTypicalRayProducer()
{
	delete[] m_ImageData;
}

void mvtkTypicalRayProducer::SetViewPort(int width,int height)
{
	m_ViewPort[0]=width;
	m_ViewPort[1]=height;
}
void mvtkTypicalRayProducer::SetVolSize(const int volDims[3],const float volSpacings[3])
{
	m_VolDims[0]=volDims[0];
	m_VolDims[1]=volDims[1];
	m_VolDims[2]=volDims[2];

	m_VolSpacings[0]=volSpacings[0];
	m_VolSpacings[1]=volSpacings[1];
	m_VolSpacings[2]=volSpacings[2];

	m_VolSize[0]=volDims[0]*volSpacings[0];
	m_VolSize[1]=volDims[1]*volSpacings[1];
	m_VolSize[2]=volDims[2]*volSpacings[2];
}

void mvtkTypicalRayProducer::GetVolSize(int volDims[3],float volSpacings[3])
{
	volDims[0]=m_VolDims[0];
	volDims[1]=m_VolDims[1];
	volDims[2]=m_VolDims[2];

	volSpacings[0]=m_VolSpacings[0];
	volSpacings[1]=m_VolSpacings[1];
	volSpacings[2]=m_VolSpacings[2];
}

void mvtkTypicalRayProducer::SetViewMatrix(const mvtkMatrix4x4& ViewMatrix)
{
	m_ViewMatrix=ViewMatrix;
}
void mvtkTypicalRayProducer::SetProjectionMatrix(const mvtkMatrix4x4& ProjectionMatrix)
{
	m_ProjectionMatrix=ProjectionMatrix;
}

void mvtkTypicalRayProducer::_calculateMatrix()
{
	mvtkMatrix4x4 modelViewMatrix
		=m_ViewMatrix*mvtkMatrix4x4::TranslateMatrix(-m_VolSize[0]*0.5f,-m_VolSize[1]*0.5f,-m_VolSize[2]*0.5f);

	mvtkMatrix4x4 invertModelViewMatrix=modelViewMatrix;
	invertModelViewMatrix.Inverse();

	m_CameraPos[0]=invertModelViewMatrix[12]/invertModelViewMatrix[15];
	m_CameraPos[1]=invertModelViewMatrix[13]/invertModelViewMatrix[15];
	m_CameraPos[2]=invertModelViewMatrix[14]/invertModelViewMatrix[15];

	
	m_ModelToVolumeMatrix.ele[0]  = 1.0f/m_VolSpacings[0];
	m_ModelToVolumeMatrix.ele[1]  = m_ModelToVolumeMatrix.ele[2] = m_ModelToVolumeMatrix.ele[3] = m_ModelToVolumeMatrix.ele[4] = 0.0f;
	m_ModelToVolumeMatrix.ele[5]  = 1.0f/m_VolSpacings[1];
	m_ModelToVolumeMatrix.ele[6]  = m_ModelToVolumeMatrix.ele[7] = m_ModelToVolumeMatrix.ele[8] = m_ModelToVolumeMatrix.ele[9] = 0.0f;
	m_ModelToVolumeMatrix.ele[10] = 1.0f/m_VolSpacings[2];
	m_ModelToVolumeMatrix.ele[11] = 0.0f;
	m_ModelToVolumeMatrix.ele[12] = 0.0f;
	m_ModelToVolumeMatrix.ele[13] = 0.0f;
	m_ModelToVolumeMatrix.ele[14] = 0.0f;
	m_ModelToVolumeMatrix.ele[15] = 1.0f;	
	
	 
	mvtkMatrix4x4 ViewToPixelsMatrix;
	ViewToPixelsMatrix.ele[0]  = 0.5f * m_ViewPort[0];
	ViewToPixelsMatrix.ele[1]  = ViewToPixelsMatrix.ele[2] = ViewToPixelsMatrix.ele[3] = ViewToPixelsMatrix.ele[4] = 0.0f;
	ViewToPixelsMatrix.ele[5]  = 0.5f * m_ViewPort[1];
	ViewToPixelsMatrix.ele[6]  = ViewToPixelsMatrix.ele[7] = ViewToPixelsMatrix.ele[8] = ViewToPixelsMatrix.ele[9] = 0.0f;
	ViewToPixelsMatrix.ele[10] = 0.5f;
	ViewToPixelsMatrix.ele[11] = 0.0f;
	ViewToPixelsMatrix.ele[12] = ViewToPixelsMatrix.ele[0]; 
	ViewToPixelsMatrix.ele[13] = ViewToPixelsMatrix.ele[5]; 
	ViewToPixelsMatrix.ele[14] = ViewToPixelsMatrix.ele[10]; 
	ViewToPixelsMatrix.ele[15] = 1.0f;

	m_PixelsToViewMatrix=ViewToPixelsMatrix;
	m_PixelsToViewMatrix.Inverse();

	m_ModelToPixelsMatrix = ViewToPixelsMatrix*m_ProjectionMatrix*modelViewMatrix;
	m_PixelsToModelMatrix=m_ModelToPixelsMatrix;
	m_PixelsToModelMatrix.Inverse();

}
bool mvtkTypicalRayProducer::_calculateBounds()
{
	float minX, minY, maxX, maxY;
	mvtkVector4 ModelPoint;	
	mvtkVector4 PixelPoint;
	if (m_CameraPos[0] >= 0 &&
	m_CameraPos[0] <= m_VolSize[0] &&
	m_CameraPos[1] >= 0 &&
	m_CameraPos[1] <= m_VolSize[1] &&
	m_CameraPos[2] >= 0 &&
	m_CameraPos[2] <= m_VolSize[2])
	{
		minX = 0;
		maxX = (float)m_ViewPort[0];
		minY = 0;
		maxY = (float)m_ViewPort[1];
	}
	else
	{
		ModelPoint[3]=1.0f;
		ModelPoint[0]=0.0f;ModelPoint[1]=0.0f;ModelPoint[2]=0.0f;
		PixelPoint=m_ModelToPixelsMatrix*ModelPoint;
		PixelPoint*=1.0f/PixelPoint[3];
		minX=maxX=PixelPoint[0];
		minY=maxY=PixelPoint[1];

		ModelPoint[0]=m_VolSize[0];ModelPoint[1]=0.0f;ModelPoint[2]=0.0f;
		PixelPoint=m_ModelToPixelsMatrix*ModelPoint;
		PixelPoint*=1.0f/PixelPoint[3];
		minX=min(minX,PixelPoint[0]);
		maxX=max(maxX,PixelPoint[0]);
		minY=min(minY,PixelPoint[1]);
		maxY=max(maxY,PixelPoint[1]);
		
		ModelPoint[0]=0.0f;ModelPoint[1]=m_VolSize[1];ModelPoint[2]=0.0f;
		PixelPoint=m_ModelToPixelsMatrix*ModelPoint;
		PixelPoint*=1.0f/PixelPoint[3];
		minX=min(minX,PixelPoint[0]);
		maxX=max(maxX,PixelPoint[0]);
		minY=min(minY,PixelPoint[1]);
		maxY=max(maxY,PixelPoint[1]);

		ModelPoint[0]=m_VolSize[0];ModelPoint[1]=m_VolSize[1];ModelPoint[2]=0.0f;
		PixelPoint=m_ModelToPixelsMatrix*ModelPoint;
		PixelPoint*=1.0f/PixelPoint[3];
		minX=min(minX,PixelPoint[0]);
		maxX=max(maxX,PixelPoint[0]);
		minY=min(minY,PixelPoint[1]);
		maxY=max(maxY,PixelPoint[1]);
		
		ModelPoint[0]=0.0f;ModelPoint[1]=0.0f;ModelPoint[2]=m_VolSize[2];
		PixelPoint=m_ModelToPixelsMatrix*ModelPoint;
		PixelPoint*=1.0f/PixelPoint[3];
		minX=min(minX,PixelPoint[0]);
		maxX=max(maxX,PixelPoint[0]);
		minY=min(minY,PixelPoint[1]);
		maxY=max(maxY,PixelPoint[1]);

		ModelPoint[0]=m_VolSize[0];ModelPoint[1]=0.0f;ModelPoint[2]=m_VolSize[2];
		PixelPoint=m_ModelToPixelsMatrix*ModelPoint;
		PixelPoint*=1.0f/PixelPoint[3];
		minX=min(minX,PixelPoint[0]);
		maxX=max(maxX,PixelPoint[0]);
		minY=min(minY,PixelPoint[1]);
		maxY=max(maxY,PixelPoint[1]);

		ModelPoint[0]=0.0f;ModelPoint[1]=m_VolSize[1];ModelPoint[2]=m_VolSize[2];
		PixelPoint=m_ModelToPixelsMatrix*ModelPoint;
		PixelPoint*=1.0f/PixelPoint[3];
		minX=min(minX,PixelPoint[0]);
		maxX=max(maxX,PixelPoint[0]);
		minY=min(minY,PixelPoint[1]);
		maxY=max(maxY,PixelPoint[1]);
		
		ModelPoint[0]=m_VolSize[0];ModelPoint[1]=m_VolSize[1];ModelPoint[2]=m_VolSize[2];
		PixelPoint=m_ModelToPixelsMatrix*ModelPoint;
		PixelPoint*=1.0f/PixelPoint[3];
		minX=min(minX,PixelPoint[0]);
		maxX=max(maxX,PixelPoint[0]);
		minY=min(minY,PixelPoint[1]);
		maxY=max(maxY,PixelPoint[1]);		
	}
	if ((minX < 0 && maxX < 0) ||
		(minY < 0 && maxY < 0) ||
		(minX > (m_ViewPort[0] - 1) &&	maxX > (m_ViewPort[0] - 1)) ||
		(minY > (m_ViewPort[1] - 1) &&	maxY > (m_ViewPort[1] - 1)))
	{
			return false;
	}
	minX=max(minX,0.0f);
	maxX=min(maxX,m_ViewPort[0]);
	minY=max(minY,0.0f);
	maxY=min(maxY,m_ViewPort[1]);

	m_ImageInUseSize[0] = (int) (maxX - minX + 1.0f);
	m_ImageInUseSize[1] = (int) (maxY - minY + 1.0f);

	m_ImageOrigin[0] = (int) minX;
	m_ImageOrigin[1] = (int) minY;

	return true;
}

void mvtkTypicalRayProducer::UpdateMatrixAndBounds()
{
	_calculateMatrix();
	if (!_calculateBounds()) return;

	delete[] m_ImageData;
	m_ImageData=new float[m_ImageInUseSize[0]*m_ImageInUseSize[1]*4];
}

void mvtkTypicalRayProducer::GetImageInUseSize(int imageSize[2])
{
	imageSize[0]=m_ImageInUseSize[0];
	imageSize[1]=m_ImageInUseSize[1];
}
void mvtkTypicalRayProducer::GetImageOrigin(int imageOrigin[2])
{
	imageOrigin[0]=m_ImageOrigin[0];
	imageOrigin[1]=m_ImageOrigin[1];
}
void mvtkTypicalRayProducer::RenderImage()
{
	if (!m_ImageData) return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
	glWindowPos2i(m_ImageOrigin[0], m_ImageOrigin[1]);
	glDrawPixels(m_ImageInUseSize[0], m_ImageInUseSize[1], GL_RGBA, GL_FLOAT,m_ImageData);
}
