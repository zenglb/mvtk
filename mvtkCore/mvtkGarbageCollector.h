#ifndef __mvtkGarbageCollector_h
#define __mvtkGarbageCollector_h

#include "mvtkObject.h"

//����������
class MVTK_COMMON_API mvtkGarbageCollector
{
public:
	//����ģʽ
	static mvtkGarbageCollector* GetGarbageCollector();
	//���
	void AddObject(mvtkObject* obj);
	//ɾ��
	void RemoveObject(mvtkObject* obj);
	//ɾ������
	void RemoveAllObject();

private:
	mvtkGarbageCollector();
	~mvtkGarbageCollector();
	//˽�з��� �����ϱ�������
	//bool remove_if_check(mvtkObject* obj);
	list<mvtkObject*>* m_ObjectCollection;
	static mvtkGarbageCollector* m_GarbageCollector;
};

#endif
