#include "vector.h"
//#include <gl\gl.h>	


//------------------------------------------------------------------//
//- float ComputeDotProduct(CVector3*, CVector3*) ----------------------//
//------------------------------------------------------------------//
//- Description: Returns the dot product of two vectors (this stuff-//
//-              is pretty self explanatory, eh?).				   -//
//------------------------------------------------------------------//
float DotProduct(const CVector3 &v1, const CVector3 &v2)
{
	return (v1.x*v2.x)+(v1.y*v2.y)+(v1.z*v2.z);
};

//------------------------------------------------------------------//
//- CVector3 ComputeCrossProduct(CVector3*, CVector3*) -------------------//
//------------------------------------------------------------------//
//- Description: Returns the cross product of two vectors.		   -//
//------------------------------------------------------------------//
CVector3 CrossProduct(const CVector3 &v1, const CVector3 &v2)
{
	CVector3 result(0.0f, 0.0f, 0.0f);

	result.x= (v1.y*v2.z) - (v1.z*v2.y);
	result.y= (v1.z*v2.x) - (v1.x*v2.z);
	result.z= (v1.x*v2.y) - (v1.y*v2.x);

	return result;
};



/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the magnitude of a vector
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float Magnitude(CVector3 vNormal)
{
	// Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2) : Where V is the vector
	return (float)sqrt( (vNormal.x * vNormal.x) + 
						(vNormal.y * vNormal.y) + 
						(vNormal.z * vNormal.z) );
}


/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns a normalize vector (A vector exactly of length 1)
/////
/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector3 Normalize(CVector3 vVector)
{
	// Get the magnitude of our normal
	float magnitude = Magnitude(vVector);				

	// Now that we have the magnitude, we can divide our vector by that magnitude.
	// That will make our vector a total length of 1.  
	vVector = vVector / magnitude;		
	
	// Finally, return our normalized vector
	return vVector;										
}
bool SameSign(float f1,float f2)
{
	return f1<0&&f2<0||f1>0&&f2>0||f1==0&&f2==0?true:false;
}
//判断点vPnt是否在射线(起点是vPtStart,方向是vDrct)上
bool PntFrontOrBack(const CVector3 &vPnt,const CVector3 &vPtStart,const CVector3 &vDrct)
{
	return SameSign(vPnt.x-vPtStart.x,vDrct.x)&&
		SameSign(vPnt.y-vPtStart.y,vDrct.y)&&
		SameSign(vPnt.z-vPtStart.z,vDrct.z)?true:false;
}
bool PntFrontOrBack2(const CVector3 &vPnt,const CVector3 &vPtStart,const CVector3 &vDrct)
{
	return SameSign(vPnt.x-vPtStart.x,vDrct.x)&&
	//	SameSign(vPnt.y-vPtStart.y,vDrct.y)&&
		SameSign(vPnt.z-vPtStart.z,vDrct.z)?true:false;
}
float Dist(const CVector3 &v1,const CVector3 &v2)
{
	return float(sqrt((v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y)+(v1.z-v2.z)*(v1.z-v2.z)));
}