//#ifndef __mvtkRCPtr_h
//#define __mvtkRCPtr_h
//
///// mvtkRCPtr - a smart pointer class
/////////////////////////////////////////////////////////////////////////////
///// mvtkRCPtr is a smart pointer class
//template<class T>
//class mvtkRCPtr
//{
//public:
//	mvtkRCPtr(T* realPtr = 0)
//	{
//		m_Pointee = realPtr;
//		if(m_Pointee)	m_Pointee->AddReference();
//	}
//
//	~mvtkRCPtr()
//	{
//		if(m_Pointee)    m_Pointee->RemoveReference();
//	}
//	
//	mvtkRCPtr& operator=(T* realPtr);
//
//	T* operator->() const {return m_Pointee;}
//	T& operator*() const  {return *m_Pointee;} 
//	operator T*() {return m_Pointee;}
//	operator T const *() const {return m_Pointee;}
//private:
//	T *m_Pointee; 
//
//	mvtkRCPtr(const mvtkRCPtr&) {}
//	void operator=(const mvtkRCPtr&) {}	
//};
////---------------------------------------------------------------------------
//template<class T>
//inline mvtkRCPtr<T>& mvtkRCPtr<T>::operator=(T* realPtr)
//{
//	if(realPtr == m_Pointee) return *this;
//	if(m_Pointee) m_Pointee->RemoveReference();
//	m_Pointee = realPtr;
//	if (m_Pointee) m_Pointee->AddReference();
//	return *this;
//}
////---------------------------------------------------------------------------
//
// 
////#define DEFINED_mvtkRCPtr
//
//
//
//#endif
//
