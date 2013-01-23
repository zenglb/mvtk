#ifndef __mvtkAbstract_Scene_h
#define __mvtkAbstract_Scene_h

#include "mvtkGlobal.h"

class MVTK_COMMON_API mvtkAbstractScene
{
public:
	mvtkAbstractScene(){}
	virtual ~mvtkAbstractScene(){}

	virtual void Init(){};
	virtual void Render()=0;
	virtual void Resize(int width, int height)=0;
	virtual void Destroy(){};

	virtual void Keyboard ( unsigned char key, int x, int y, bool &redisplay) {}
	virtual void Speckey(int key, int x, int y, bool &redisplay) {}
	
	virtual void LButtonDown(int x, int y, bool &redisplay){}
	virtual void LButtonUp(int x, int y, bool &redisplay){}

	virtual void MButtonDown(int x, int y, bool &redisplay){}
	virtual void MButtonUp(int x, int y, bool &redisplay){}

	virtual void RButtonDown(int x, int y, bool &redisplay){}
	virtual void RButtonUp(int x, int y, bool &redisplay){}

	virtual void Wheel(int value, bool &redisplay){}
	
	virtual void MouseMove(int x, int y, bool &redisplay){}

};

#endif