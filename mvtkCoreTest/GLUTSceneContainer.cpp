#include "GLUTSceneContainer.h"
#include "mvtkAbstractScene.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP   3
#  define GLUT_WHEEL_DOWN 4
#endif

GLUTSceneContainer* GLUTSceneContainer::GetMainWindow()
{
	if (!s_pMainWindow)
		s_pMainWindow=new GLUTSceneContainer;
	return s_pMainWindow;
}
	
void GLUTSceneContainer::SetSize(int width,int height)
{
	m_Size[0]=width;
	m_Size[1]=height;
}

void GLUTSceneContainer::GetSize(int &width,int &height) const
{
	width=m_Size[0];
	height=m_Size[1];
}

void GLUTSceneContainer::SetTitle(const char* title)
{
	strcpy(m_Title,title);
}

const char* GLUTSceneContainer::GetTitle() const
{
	return m_Title;
}

void GLUTSceneContainer::SetScene(mvtkAbstractScene* scene)
{
	m_Scene=scene;
}

mvtkAbstractScene* GLUTSceneContainer::GetScene() const
{
	return m_Scene;
}

void GLUTSceneContainer::Create(int posX,int posY)
{
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowPosition(posX,posY);
	glutInitWindowSize(m_Size[0],m_Size[1]);
	m_WindowID=glutCreateWindow(m_Title);
	if (m_FullScreen) glutFullScreen();
	
	if (m_Scene) m_Scene->Init();

	glutDisplayFunc(s_display);
	glutKeyboardFunc(s_keyboard); 
	glutSpecialFunc(s_speckey);
	glutReshapeFunc(s_reshape);
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);

	glutMainLoop();
}

void GLUTSceneContainer::s_display()
{
	if (s_pMainWindow->m_Scene) s_pMainWindow->m_Scene->Render();
	glutSwapBuffers();
}

void GLUTSceneContainer::s_keyboard ( unsigned char key, int x, int y)
{
	if (key==27) 
	{
		if (s_pMainWindow->m_Scene) s_pMainWindow->m_Scene->Destroy();
		Exit(0);
	}
	else 
	{
		bool redis=false;
		if (s_pMainWindow->m_Scene) s_pMainWindow->m_Scene->Keyboard(key,x,y,redis);
		if (redis) glutPostRedisplay();
	}
}

void GLUTSceneContainer::s_speckey(GLint key, GLint x, GLint y)
{
	bool redis=false;
	if (s_pMainWindow->m_Scene) s_pMainWindow->m_Scene->Speckey(key,x,y,redis);
	if (redis) glutPostRedisplay();
}

void GLUTSceneContainer::s_reshape(int width, int height)
{
	if (s_pMainWindow->m_Scene) s_pMainWindow->m_Scene->Resize(width,height);
	glutPostRedisplay();
}

void GLUTSceneContainer::s_mouse(int button, int state, int x, int y)
{
	if (!s_pMainWindow->m_Scene) return;
	bool redis=false;
	if (button==GLUT_LEFT_BUTTON)
	{
		if (state==GLUT_DOWN) s_pMainWindow->m_Scene->LButtonDown(x,y,redis);
		else if (state==GLUT_UP) s_pMainWindow->m_Scene->LButtonUp(x,y,redis);
	}
	else if (button==GLUT_MIDDLE_BUTTON)
	{
		if (state==GLUT_DOWN) s_pMainWindow->m_Scene->MButtonDown(x,y,redis);
		else if (state==GLUT_UP) s_pMainWindow->m_Scene->MButtonUp(x,y,redis);
	}
	else if (button==GLUT_RIGHT_BUTTON)
	{
		if (state==GLUT_DOWN) s_pMainWindow->m_Scene->RButtonDown(x,y,redis);
		else if (state==GLUT_UP) s_pMainWindow->m_Scene->RButtonUp(x,y,redis);
	}
	else if (button==GLUT_WHEEL_UP) s_pMainWindow->m_Scene->Wheel(+1,redis);
	else if (button==GLUT_WHEEL_DOWN) s_pMainWindow->m_Scene->Wheel(-1,redis);
	if (redis) glutPostRedisplay();

}

void GLUTSceneContainer::s_motion(int x, int y)
{
	bool redis=false;
	if (s_pMainWindow->m_Scene) s_pMainWindow->m_Scene->MouseMove(x,y,redis);
	if (redis) glutPostRedisplay();
}

GLUTSceneContainer::GLUTSceneContainer()
{
	m_Size[0]=640;
	m_Size[1]=480;
	m_Title[0]=0;
	m_FullScreen=false;
	m_WindowID=0;
	m_Scene=0;
}

GLUTSceneContainer::~GLUTSceneContainer()
{
}

void GLUTSceneContainer::Exit(int i)
{
	if (s_pMainWindow) delete s_pMainWindow;
	exit(i);
}

GLUTSceneContainer* GLUTSceneContainer::s_pMainWindow=0;

