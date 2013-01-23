#ifndef _mvtkVector2_h
#define _mvtkVector2_h

#include <math.h>
#include "mvtkGlobal.h"

class MVTK_COMMON_API mvtkVector2
{
public:
	float ele[2];
	mvtkVector2()
	{
		ele[0] = 0.0f;
		ele[1] = 0.0f;
	}
	mvtkVector2(const mvtkVector2 &v)
	{
		ele[0] = v.ele[0];
		ele[1] = v.ele[1];
	}
	mvtkVector2(float x, float y)
	{
		ele[0] = x;
		ele[1] = y;
	}
	mvtkVector2(float srcVector[2])
	{
		ele[0] = srcVector[0];
		ele[1] = srcVector[1];
	}
	operator float* () { return ele; }	
	operator const float* () const { return ele; }

	mvtkVector2& operator = (const mvtkVector2 &a)
	{
		ele[0] = a.ele[0];
		ele[1] = a.ele[1];
		return *this; 
	}
	mvtkVector2& operator *= (float);
	mvtkVector2& operator += (const mvtkVector2 &);
	mvtkVector2& operator -= (const mvtkVector2 &);

	void Normalize();
	float Length();
};

inline float operator * (const mvtkVector2& A, const mvtkVector2& B) 
{
	return A.ele[0]*B.ele[0] + A.ele[1]*B.ele[1];
}
//----------------------------------------------------------------------------
inline mvtkVector2 operator * (const mvtkVector2 &V, float s) 
{
	mvtkVector2 Res;
	Res.ele[0] = V.ele[0] * s;
	Res.ele[1] = V.ele[1] * s;
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector2 operator * (float s, const mvtkVector2 &V) 
{
	mvtkVector2 Res;
	Res.ele[0] = V.ele[0] * s;
	Res.ele[1] = V.ele[1] * s;
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector2& mvtkVector2::operator *= (float s) 
{
	ele[0] *= s;
	ele[1] *= s;
	return *this;
}
//----------------------------------------------------------------------------
inline mvtkVector2 operator + (const mvtkVector2& A, const mvtkVector2& B) 
{
	mvtkVector2 Res;
	Res.ele[0] = A.ele[0] + B.ele[0];
	Res.ele[1] = A.ele[1] + B.ele[1];
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector2 operator - (const mvtkVector2& A, const mvtkVector2& B) 
{
	mvtkVector2 Res;
	Res.ele[0] = A.ele[0] - B.ele[0];
	Res.ele[1] = A.ele[1] - B.ele[1];
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector2 operator - (const mvtkVector2& A)
{
	mvtkVector2 Res;
	Res.ele[0] = - A.ele[0];
	Res.ele[1] = - A.ele[1];
	return Res;
}
//----------------------------------------------------------------------------
inline mvtkVector2 & mvtkVector2::operator += (const mvtkVector2 &B) 
{
	ele[0] += B.ele[0];
	ele[1] += B.ele[1];
	return *this;
}
//----------------------------------------------------------------------------
inline mvtkVector2 & mvtkVector2::operator -= (const mvtkVector2 &B) 
{
	ele[0] -= B.ele[0];
	ele[1] -= B.ele[1];
	return *this;
}
//----------------------------------------------------------------------------
inline void mvtkVector2::Normalize() 
{
	float vecLenInv = 1.0f / sqrtf(ele[0]*ele[0] + ele[1]*ele[1]);
	ele[0] *= vecLenInv;
	ele[1] *= vecLenInv;
}
//----------------------------------------------------------------------------
inline float mvtkVector2::Length()
{
	return sqrtf(ele[0]*ele[0] + ele[1]*ele[1] );
}


#endif
