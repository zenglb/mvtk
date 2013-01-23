#ifndef GLUT_Scene_Container_h
#define GLUT_Scene_Container_h

#include "GL/glut.h"

class mvtkAbstractScene;
class GLUTSceneContainer
{
public:
	static GLUTSceneContainer* GetMainWindow();	
	void SetSize(int width,int height);
	void GetSize(int &width,int &height) const;
	void SetTitle(const char* title);
	const char* GetTitle() const;
	void SetScene(mvtkAbstractScene* scene);
	mvtkAbstractScene* GetScene() const;
	void Create(int posX=0,int posY=0);

private:
	GLUTSceneContainer();
	virtual ~GLUTSceneContainer();

	static GLUTSceneContainer *s_pMainWindow;
	static void Exit(int i);

	static void s_display();
	static void s_keyboard ( unsigned char key, int x, int y);
	static void s_speckey(GLint key, GLint x, GLint y);
	static void s_reshape(int width, int height);
	static void s_mouse(int button, int state, int x, int y);
	static void s_motion(int x, int y);


	char m_Title[1024];
	int m_Size[2];
	bool m_FullScreen;
	int m_WindowID;

	mvtkAbstractScene *m_Scene;
}; 


#endif