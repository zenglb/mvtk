#include "mvtkScene.h"
#include "GL/gl.h"

static const float pi=3.1415926536f;

mvtkScene::mvtkScene()
{
	m_Fovy=45.0f;
	m_Near=1.0f;
	m_Far=2.0f;
	m_Translate[0]=m_Translate[1]=m_Translate[2]=0.0f;
	m_Scale=1.0f;

	m_NeedCalculateCamera=true;
	m_NeedCalculateMatrix=true;

	m_RadPerPixel=0.005f;
	m_ScaleRatePerPixel=logf(1.002f);

	m_Rotating=false;
	m_Scaling=false;
	m_Moving=false;
}

mvtkScene::~mvtkScene()
{

}

void mvtkScene::SetFovy(float fovy)
{
	m_Fovy=fovy;
	m_NeedCalculateCamera=true;
}

void mvtkScene::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
	m_ViewPort[0]=width;
	m_ViewPort[1]=height;

	m_NeedCalculateMatrix=true;
}
void mvtkScene::_calculateCamera()
{
	float size[3];
	GetSize3D(size);
	float d=sqrt(size[0]*size[0]+size[1]*size[1]+size[2]*size[2]);
	float r=d/2.0f;

	float sin1=sinf(m_Fovy*pi/360.0f);
	m_ZTranslateBase=-r/sin1;

	m_Near=(-m_ZTranslateBase-r)/5.0f;
	m_Far=5.0f*(-m_ZTranslateBase+r);
	
	m_NeedCalculateMatrix=true;
} 

void mvtkScene::SetSize3DModified()
{
	m_Translate[0]=m_Translate[1]=m_Translate[2]=0.0f;
	m_Scale=1.0f;
	m_Rotation.Identity();
	m_NeedCalculateCamera=true;
}

void mvtkScene::_calculateMatrix()
{
	m_ViewMatrix=mvtkMatrix4x4::TranslateMatrix(m_Translate[0],m_Translate[1],m_ZTranslateBase+m_Translate[2])
		*mvtkMatrix4x4::ScaleMatrix(m_Scale,m_Scale,m_Scale)*m_Rotation.ToMatrix();
		
	float halfFrustumHeight=m_Near*tanf(m_Fovy*pi/360.0f);
	float halfFrustumWidth=halfFrustumHeight/m_ViewPort[1]*m_ViewPort[0];

	float *projMat=m_ProjectionMatrix.ele;
	projMat[0]=m_Near/halfFrustumWidth;
	projMat[1]=projMat[2]=projMat[3]=projMat[4]=0.0f;
	projMat[5]=m_Near/halfFrustumHeight;
	projMat[6]=projMat[7]=projMat[8]=projMat[9]=0.0f;
	projMat[10]=-(m_Far+m_Near)/(m_Far-m_Near);
	projMat[11]=-1.0f;
	projMat[12]=projMat[13]=0.0f;
	projMat[14]=-2.0f*m_Far*m_Near/(m_Far-m_Near);
	projMat[15]=0.0f;

}

void mvtkScene::Render()
{
	if (m_NeedCalculateCamera) 
	{
		_calculateCamera();
		m_NeedCalculateCamera=false;

	}
	if (m_NeedCalculateMatrix) 
	{
		_calculateMatrix();
		m_NeedCalculateMatrix=false;
	}
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_ViewMatrix);

	RenderContent();

}

// Default Content : Draw a Box 
void mvtkScene::RenderContent()
{
	glClearColor(0.5f,0.5f,0.5f,1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBegin(GL_QUADS);

	glColor3f(1.0f,0.0f,0.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);

	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,-1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);

	glColor3f(0.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);
	glVertex3f(-1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);

	glColor3f(1.0f,0.0f,1.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,1.0f);
	glVertex3f(1.0f,-1.0f,-1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);

	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(1.0f,1.0f,1.0f);
	glVertex3f(1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,-1.0f);
	glVertex3f(-1.0f,1.0f,1.0f);

	glEnd();

}

void mvtkScene::GetSize3D(float size3D[3])
{
	size3D[0]=size3D[1]=size3D[2]=2.0f;
}

// End: Default Content

const mvtkMatrix4x4& mvtkScene::GetViewMatrix()
{
	return m_ViewMatrix;
}
const mvtkMatrix4x4& mvtkScene::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

void mvtkScene::_makeReference()
{
	m_OldTranslate[0]=m_Translate[0]; m_OldTranslate[1]=m_Translate[1]; m_OldTranslate[2]=m_Translate[2];
	m_OldScale=m_Scale;
	m_OldRotation=m_Rotation;
}

void mvtkScene::LButtonDown(int x, int y, bool &redisplay)
{
	_makeReference();
	m_OldMouseX=x;
	m_OldMouseY=y;
	m_Rotating=true;
}

void mvtkScene::LButtonUp(int x, int y, bool &redisplay)
{
	m_Rotating=false;
}

void mvtkScene::MButtonDown(int x, int y, bool &redisplay)
{
	_makeReference();
	m_OldMouseX=x;
	m_OldMouseY=y;
	m_Moving=true;
}

void mvtkScene::MButtonUp(int x, int y, bool &redisplay)
{
	m_Moving=false;
}

void mvtkScene::RButtonDown(int x, int y, bool &redisplay)
{
	_makeReference();
	m_OldMouseX=x;
	m_OldMouseY=y;
	m_Scaling=true;
}

void mvtkScene::RButtonUp(int x, int y, bool &redisplay)
{
	m_Scaling=false;
}

void mvtkScene::MouseMove(int x, int y, bool &redisplay)
{
	int dx,dy;
	if (m_Rotating || m_Moving || m_Scaling)
	{
		dx=x-m_OldMouseX; 
		dy=-(y-m_OldMouseY);

		if (dx==0 && dy==0) return;
	
		if (m_Rotating) 
		{
			mvtkVector4 v;
			v[0]=(float)dx; 
			v[1]=(float)dy;
			v[2]=v[3]=0.0f;

			mvtkVector4 vz;
			vz[0]=vz[1]=vz[3]=0.0f;
			vz[2]=1.0f;

			v=vz%v;

			float length=v.Length();
			v*=1.0f/length;

			m_Rotation=mvtkQuaternion(v[0],v[1],v[2],length*m_RadPerPixel)*m_OldRotation;
			m_NeedCalculateMatrix=true;
			redisplay=true;

		}	
		else if (m_Moving) 
		{
			float d_eye=(m_ViewPort[1]*0.5f)/tanf(m_Fovy*pi/360.0f);
			m_Translate[0]=m_OldTranslate[0]-(float)dx/d_eye*m_ZTranslateBase; 
			m_Translate[1]=m_OldTranslate[1]-(float)dy/d_eye*m_ZTranslateBase;
			m_NeedCalculateMatrix=true;
			redisplay=true;
		}
		else if (m_Scaling) 
		{
			m_Scale=m_OldScale*expf(m_ScaleRatePerPixel*(float)dy);
			m_NeedCalculateMatrix=true;
			redisplay=true;
		}
	}
}

void mvtkScene::GetTranslate(float translate[3])
{
	translate[0]=m_Translate[0];
	translate[1]=m_Translate[1];
	translate[2]=m_Translate[2];
}

void mvtkScene::SetTranslate(const float translate[3])
{
	m_Translate[0]=translate[0];
	m_Translate[1]=translate[1];
	m_Translate[2]=translate[2];
	m_NeedCalculateMatrix=true;	
}

void mvtkScene::SetScale(float scale)
{
	m_Scale=scale;
	m_NeedCalculateMatrix=true;	
}
void mvtkScene::SetRotation(const mvtkQuaternion& rotation)
{
	m_Rotation=rotation;
	m_NeedCalculateMatrix=true;	
}
