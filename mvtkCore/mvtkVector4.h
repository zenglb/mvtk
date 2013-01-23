#ifndef _mvtkVector4_h
#define _mvtkVector4_h

#include <math.h>
#include "mvtkGlobal.h"

class MVTK_COMMON_API mvtkVector4
{
public:
	float ele[4];
	mvtkVector4()
	{
		ele[0] = 0.0f;
		ele[1] = 0.0f;
		ele[2] = 0.0f;
		ele[3] = 1.0f;
	}
	mvtkVector4(const mvtkVector4 &v)
	{
		ele[0] = v.ele[0];
		ele[1] = v.ele[1];
		ele[2] = v.ele[2];
		ele[3] = v.ele[3];
	}
	mvtkVector4(float x, float y, float z, float w = 1.0f)
	{
		ele[0] = x;
		ele[1] = y;
		ele[2] = z;
		ele[3] = w;
	}
	mvtkVector4(float srcVector[4])
	{
		ele[0] = srcVector[0];
		ele[1] = srcVector[1];
		ele[2] = srcVector[2];
		ele[3] = srcVector[3];
	}
	operator float* () { return ele; }	
	operator const float* () const { return ele; }

	mvtkVector4& operator = (const mvtkVector4 &a)
	{
		ele[0] = a.ele[0];
		ele[1] = a.ele[1];
		ele[2] = a.ele[2];
		ele[3] = a.ele[3];
		return *this; 
	}
	mvtkVector4& operator *= (float);
	mvtkVector4& operator += (const mvtkVector4 &);
	mvtkVector4& operator -= (const mvtkVector4 &);

	void Normalize();
	float Length();
};

inline float operator * (const mvtkVector4& A, const mvtkVector4& B) 
{
	return A.ele[0]*B.ele[0] + A.ele[1]*B.ele[1] + A.ele[2]*B.ele[2];
}
//----------------------------------------------------------------------------
inline mvtkVector4 operator % (const mvtkVector4& A, const mvtkVector4& B) 
{
	mvtkVector4 Res;
	Res.ele[0] = A.ele[1] * B.ele[2] - A.ele[2] * B.ele[1]; 
	Res.ele[1] = A.ele[2] * B.ele[0] - A.ele[0] * B.ele[2]; 
	Res.ele[2] = A.ele[0] * B.ele[1] - A.ele[1] * B.ele[0]; 
	Res.ele[3] = 0.0f;
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector4 operator * (const mvtkVector4 &V, float s) 
{
	mvtkVector4 Res;
	Res.ele[0] = V.ele[0] * s;
	Res.ele[1] = V.ele[1] * s;
	Res.ele[2] = V.ele[2] * s;
	Res.ele[3] = V.ele[3] * s;	
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector4 operator * (float s, const mvtkVector4 &V) 
{
	mvtkVector4 Res;
	Res.ele[0] = V.ele[0] * s;
	Res.ele[1] = V.ele[1] * s;
	Res.ele[2] = V.ele[2] * s;
	Res.ele[3] = V.ele[3] * s;	
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector4& mvtkVector4::operator *= (float s) 
{
	ele[0] *= s;
	ele[1] *= s;
	ele[2] *= s;
	ele[3] *= s;	
	return *this;
}
//----------------------------------------------------------------------------
inline mvtkVector4 operator + (const mvtkVector4& A, const mvtkVector4& B) 
{
	mvtkVector4 Res;
	Res.ele[0] = A.ele[0] + B.ele[0];
	Res.ele[1] = A.ele[1] + B.ele[1];
	Res.ele[2] = A.ele[2] + B.ele[2];
	Res.ele[3] = A.ele[3] + B.ele[3];
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector4 operator - (const mvtkVector4& A, const mvtkVector4& B) 
{
	mvtkVector4 Res;
	Res.ele[0] = A.ele[0] - B.ele[0];
	Res.ele[1] = A.ele[1] - B.ele[1];
	Res.ele[2] = A.ele[2] - B.ele[2];
	Res.ele[3] = A.ele[3] - B.ele[3];
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector4 operator - (const mvtkVector4& A)
{
	mvtkVector4 Res;
	Res.ele[0] = - A.ele[0];
	Res.ele[1] = - A.ele[1];
	Res.ele[2] = - A.ele[2];
	Res.ele[3] = - A.ele[3];
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector4 & mvtkVector4::operator += (const mvtkVector4 &B) 
{
	ele[0] += B.ele[0];
	ele[1] += B.ele[1];
	ele[2] += B.ele[2];
	ele[3] += B.ele[3];
	return *this;
}
//----------------------------------------------------------------------------
inline mvtkVector4 & mvtkVector4::operator -= (const mvtkVector4 &B) 
{
	ele[0] -= B.ele[0];
	ele[1] -= B.ele[1];
	ele[2] -= B.ele[2];
	ele[3] -= B.ele[3];
	return *this;
}
//----------------------------------------------------------------------------
inline void mvtkVector4::Normalize() 
{
	float vecLenInv = 1.0f / sqrtf(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
	ele[0] *= vecLenInv;
	ele[1] *= vecLenInv;
	ele[2] *= vecLenInv;
}
//----------------------------------------------------------------------------
inline float mvtkVector4::Length()
{
	return sqrtf(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
}


#endif
