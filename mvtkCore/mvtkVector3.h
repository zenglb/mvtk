#ifndef _mvtkVector3_h
#define _mvtkVector3_h

#include <math.h>
#include "mvtkGlobal.h"

class MVTK_COMMON_API mvtkVector3
{
public:
	float ele[3];
	mvtkVector3()
	{
		ele[0] = 0.0f;
		ele[1] = 0.0f;
		ele[2] = 0.0f;
	}
	mvtkVector3(const mvtkVector3 &v)
	{
		ele[0] = v.ele[0];
		ele[1] = v.ele[1];
		ele[2] = v.ele[2];
	}
	mvtkVector3(float x, float y, float z)
	{
		ele[0] = x;
		ele[1] = y;
		ele[2] = z;
	}
	mvtkVector3(float srcVector[3])
	{
		ele[0] = srcVector[0];
		ele[1] = srcVector[1];
		ele[2] = srcVector[2];
	}
	operator float* () { return ele; }	
	operator const float* () const { return ele; }

	mvtkVector3& operator = (const mvtkVector3 &a)
	{
		ele[0] = a.ele[0];
		ele[1] = a.ele[1];
		ele[2] = a.ele[2];
		return *this; 
	}
	mvtkVector3& operator *= (float);
	mvtkVector3& operator += (const mvtkVector3 &);
	mvtkVector3& operator -= (const mvtkVector3 &);

	void Normalize();
	float Length();
};

inline float operator * (const mvtkVector3& A, const mvtkVector3& B) 
{
	return A.ele[0]*B.ele[0] + A.ele[1]*B.ele[1] + A.ele[2]*B.ele[2];
}
//----------------------------------------------------------------------------
inline mvtkVector3 operator % (const mvtkVector3& A, const mvtkVector3& B) 
{
	mvtkVector3 Res;
	Res.ele[0] = A.ele[1] * B.ele[2] - A.ele[2] * B.ele[1]; 
	Res.ele[1] = A.ele[2] * B.ele[0] - A.ele[0] * B.ele[2]; 
	Res.ele[2] = A.ele[0] * B.ele[1] - A.ele[1] * B.ele[0]; 
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector3 operator * (const mvtkVector3 &V, float s) 
{
	mvtkVector3 Res;
	Res.ele[0] = V.ele[0] * s;
	Res.ele[1] = V.ele[1] * s;
	Res.ele[2] = V.ele[2] * s;
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector3 operator * (float s, const mvtkVector3 &V) 
{
	mvtkVector3 Res;
	Res.ele[0] = V.ele[0] * s;
	Res.ele[1] = V.ele[1] * s;
	Res.ele[2] = V.ele[2] * s;
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector3& mvtkVector3::operator *= (float s) 
{
	ele[0] *= s;
	ele[1] *= s;
	ele[2] *= s;
	return *this;
}
//----------------------------------------------------------------------------
inline mvtkVector3 operator + (const mvtkVector3& A, const mvtkVector3& B) 
{
	mvtkVector3 Res;
	Res.ele[0] = A.ele[0] + B.ele[0];
	Res.ele[1] = A.ele[1] + B.ele[1];
	Res.ele[2] = A.ele[2] + B.ele[2];
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector3 operator - (const mvtkVector3& A, const mvtkVector3& B) 
{
	mvtkVector3 Res;
	Res.ele[0] = A.ele[0] - B.ele[0];
	Res.ele[1] = A.ele[1] - B.ele[1];
	Res.ele[2] = A.ele[2] - B.ele[2];
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector3 operator - (const mvtkVector3& A)
{
	mvtkVector3 Res;
	Res.ele[0] = - A.ele[0];
	Res.ele[1] = - A.ele[1];
	Res.ele[2] = - A.ele[2];
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector3 & mvtkVector3::operator += (const mvtkVector3 &B) 
{
	ele[0] += B.ele[0];
	ele[1] += B.ele[1];
	ele[2] += B.ele[2];
	return *this;
}
//----------------------------------------------------------------------------
inline mvtkVector3 & mvtkVector3::operator -= (const mvtkVector3 &B) 
{
	ele[0] -= B.ele[0];
	ele[1] -= B.ele[1];
	ele[2] -= B.ele[2];
	return *this;
}
//----------------------------------------------------------------------------
inline void mvtkVector3::Normalize() 
{
	float vecLenInv = 1.0f / sqrtf(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
	ele[0] *= vecLenInv;
	ele[1] *= vecLenInv;
	ele[2] *= vecLenInv;
}
//----------------------------------------------------------------------------
inline float mvtkVector3::Length()
{
	return sqrtf(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
}


#endif
