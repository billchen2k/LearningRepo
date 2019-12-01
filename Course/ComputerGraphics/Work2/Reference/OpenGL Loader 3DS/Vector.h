#if !defined(AFX_CVECTOR3_H__A7C41EA3_DB80_49DA_9A84_72E6251F9A21__INCLUDED_)
#define AFX_CVECTOR3_H__A7C41EA3_DB80_49DA_9A84_72E6251F9A21__INCLUDED_
#include <math.h>
struct CVector3
{
	float x,y,z;
	float ComputeLength(void)
	{
		return  (float)sqrt(x*x + y*y + z*z);
	};
	CVector3 operator+ (const CVector3 &v)
	{
		return CVector3(v.x + x, v.y + y, v.z + z);		
	};
	CVector3  operator- (const CVector3 &v)
	{
		return CVector3(x - v.x, y - v.y, z - v.z);
	};
	CVector3  operator- ()
	{
		return CVector3(-x , -y , -z );
	};
	CVector3  operator* (const float scalar)
	{
		return CVector3(x * scalar,y * scalar,z * scalar);
	};
	CVector3  operator* (const CVector3 &v)
	{	
		return CVector3(x * v.x,y * v.y,z * v.z);
	};
	CVector3  operator/ (const CVector3 &v)
	{
		return CVector3(x/v.x,y/v.y,z/v.z);
	};
	CVector3  operator/ (const float scalar)
	{		
		return CVector3(x / scalar,y / scalar,z / scalar);
	};
	CVector3  &operator = (const CVector3 &v)
	{		
		x = v.x;y = v.y;z = v.z;
		return *this; 
	};
	CVector3()
	{	
		x = 0;y = 0; z = 0;	
	}
	CVector3(float x, float y, float z)
	{
		this->x = x;this->y = y;this->z = z;
	};
	CVector3(float *pXYZ)
	{
		this->x = *pXYZ;this->y = *(pXYZ+1);this->z = *(pXYZ+2);
	};
	
};

void ComputeNormal(CVector3* v1, CVector3* v2, CVector3* v3);

float DotProduct(const CVector3 &v1, const CVector3 &v2);

CVector3 CrossProduct(const CVector3 &v1, const CVector3 &v2);


float Magnitude(CVector3 vNormal);

CVector3 Normalize(CVector3 vVector);

bool PntFrontOrBack(const CVector3 &vPnt,const CVector3 &vPtStart,const CVector3 &vDrct);

bool PntFrontOrBack2(const CVector3 &vPnt,const CVector3 &vPtStart,const CVector3 &vDrct);

float Dist(const CVector3 &v1,const CVector3 &v2);
#endif