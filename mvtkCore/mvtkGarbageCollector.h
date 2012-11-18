#ifndef __mvtkGarbageCollector_h
#define __mvtkGarbageCollector_h

#include "mvtkObject.h"

//垃圾回收类
class MVTK_COMMON_API mvtkGarbageCollector
{
public:
	//单例模式
	static mvtkGarbageCollector* GetGarbageCollector();
	//添加
	void AddObject(mvtkObject* obj);
	//删除
	void RemoveObject(mvtkObject* obj);
	//删除所有
	void RemoveAllObject();

private:
	mvtkGarbageCollector();
	~mvtkGarbageCollector();
	//私有方法 供集合遍历调用
	//bool remove_if_check(mvtkObject* obj);
	list<mvtkObject*>* m_ObjectCollection;
	static mvtkGarbageCollector* m_GarbageCollector;
};

#endif
