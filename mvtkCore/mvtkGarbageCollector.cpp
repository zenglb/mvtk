#include "mvtkGarbageCollector.h"

mvtkGarbageCollector* mvtkGarbageCollector::m_GarbageCollector=NULL;

mvtkGarbageCollector* mvtkGarbageCollector::GetGarbageCollector(){
	if(mvtkGarbageCollector::m_GarbageCollector==NULL){
		mvtkGarbageCollector::m_GarbageCollector=new mvtkGarbageCollector;
	}
	return mvtkGarbageCollector::m_GarbageCollector;
}
void mvtkGarbageCollector::AddObject(mvtkObject* obj){
	this->m_ObjectCollection->push_back(obj);	
}

void mvtkGarbageCollector::RemoveObject(mvtkObject* obj){
	this->m_ObjectCollection->remove(obj);
}

bool mvtkGarbageCollector_remove_if_check(mvtkObject* obj){
	if(obj->GetReferenceCount()==0){
		obj->Delete();
		return true;
	}else{
		return false;
	}
}

void mvtkGarbageCollector::RemoveAllObject(){
	while(!this->m_ObjectCollection->empty()){
		this->m_ObjectCollection->remove_if(&mvtkGarbageCollector_remove_if_check);
	}
}

mvtkGarbageCollector::mvtkGarbageCollector(){
	this->m_ObjectCollection=new list<mvtkObject*>;
}

mvtkGarbageCollector::~mvtkGarbageCollector(){
	this->RemoveAllObject();
	delete this->m_ObjectCollection;
}