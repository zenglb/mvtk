#include "mvtkObject.h"
#include "mvtkObserver.h"
#include "mvtkGarbageCollector.h"

int  mvtkObject::IsTypeOf(const char *name){
	if ( !strcmp("mvtkObject",name) ){ 
		return 1; 
	}else{
		return 0;
	}
}

int mvtkObject::IsA(const char *name){
	return this->mvtkObject::IsTypeOf(name);
}

void mvtkObject::DebugOn(){
	this->m_Debug=1;
}

void mvtkObject::DebugOff(){
	this->m_Debug=0;
}

unsigned char mvtkObject::GetDebug(){
	return (unsigned char)this->m_Debug;
}

void mvtkObject::SetDebug(unsigned char debugFlag){
	this->m_Debug=debugFlag;
}

void mvtkObject::BreakOnError(){
}

void mvtkObject::Print(ostream& os){
	this->PrintSelf(os);
}

void mvtkObject::PrintSelf(ostream& os){
}

void mvtkObject::AddObserver(mvtkObserver* observer){
	//observer->AddReference();
	this->m_Observers->push_back(observer);
}

void mvtkObject::RemoveObserver(mvtkObserver* observer){
	//observer->RemoveReference();
	this->m_Observers->remove(observer);
	observer->Delete();
}

void mvtkObject::RemoveAllObservers(){
	list<mvtkObserver*>::iterator v;
	for(v=this->m_Observers->begin();v!=this->m_Observers->end();++v){
		(*v)->Delete();
	}
	this->m_Observers->clear();
}

//void mvtkObject::AddReference(){
//	this->m_ReferenceCount++;
//	this->Delete();
//}
//
//void mvtkObject::RemoveReference(){
//	this->m_ReferenceCount--;
//	this->Delete();
//}

void mvtkObject::Delete(){
	//if(this->m_ReferenceCount<=0){
		delete this;//¹û¶Ï»Óµ¶×Ô¹¬
	//}
}

mvtkObject::mvtkObject(){
	this->m_Observers=new list<mvtkObserver*>;
	this->m_Debug=0;
	//this->m_ReferenceCount=0;
	//mvtkGarbageCollector::GetGarbageCollector()->AddObject(this);
}

mvtkObject::~mvtkObject(){
	mvtkDebugMessage("Destructing!");

	// warn user if reference counting is on and the object is being referenced
	// by another object
	//if ( this->GetReferenceCount() > 0)
	//{
	//	mvtkErrorMessage("Trying to delete object with non-zero reference count.");
	//}

	list<mvtkObserver*>::iterator v;
	for(v=this->m_Observers->begin();v!=this->m_Observers->end();++v){
		(*v)->Delete();
	}
	//mvtkGarbageCollector::GetGarbageCollector()->RemoveObject(this);
	delete this->m_Observers;
	this->m_Observers=NULL;
}

void mvtkObject::_updateObservers(){
	list<mvtkObserver*>::iterator v;
	for(v=this->m_Observers->begin();v!=this->m_Observers->end();++v){
		(*v)->Update();
	}
}  
