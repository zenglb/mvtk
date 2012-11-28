#ifndef __mvtkProcessObject_h
#define __mvtkProcessObject_h

#include "mvtkObject.h"

/// mvtkProcessObject - abstract base class for source, filter(algorithm) and mapper
///////////////////////////////////////////////////////////////////////////
/// mvtkProcessObject is an abstract object that specifies behavior and
/// interface of source, filter and mapper.
class MVTK_COMMON_API mvtkProcessObject : public mvtkObject
{
public:
    MVTK_ABSTRACT_TYPE(mvtkProcessObject,mvtkObject)

	virtual void PrintSelf(ostream& os){}

    bool Run();

    void SetStartMethod(void (* f) (void)) {m_StartMethod = f;}
    void SetEndMethod(void (* f) (void)){m_EndMethod = f;}
    void SetProgressMethod(void (* f) (void *)){m_ProgressMethod = f;}

	///////////////////////////////////////////////////////////////////////
	/// Get current rate of process of the running process.
	/// \return Return current rate of process.
	///////////////////////////////////////////////////////////////////////
	float GetProgressRate() { return m_ProgressRate; }

protected:
	virtual ~mvtkProcessObject(){this->m_StartMethod=NULL;this->m_EndMethod=NULL;this->m_ProgressMethod=NULL;}
	mvtkProcessObject(){this->m_StartMethod=NULL;this->m_EndMethod=NULL;this->m_ProgressMethod=NULL;}

    virtual bool Execute() { return true; }
	void SetProgressRate(float rate) {m_ProgressRate = rate>100?100:rate; }
	void UpdateObservers() { this->_updateObservers(); }

	float m_ProgressRate;


    void (* m_StartMethod) (void);
    void (* m_EndMethod) (void);
    void (* m_ProgressMethod) (void *);
private:
	//mvtkProcessObject(const mvtkProcessObject&);
 //   void operator=(const mvtkProcessObject&);
};


//#define DEFINED_mvtkProcessObject



#endif


