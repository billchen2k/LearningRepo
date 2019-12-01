// Frustum.cpp: implementation of the CFrustum class.
//
//////////////////////////////////////////////////////////////////////

#include "Frustum.h"
#include "gamehead.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVector3 CFrustum::m_vPos;
CFrustum::CFrustum()
{

}

CFrustum::~CFrustum()
{

}
// We create an enum of the sides so we don't have to call each side 0 or 1.
// This way it makes it more understandable and readable when dealing with frustum sides.


///////////////////////////////// NORMALIZE PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This normalizes a plane (A side) from a given frustum.
/////
///////////////////////////////// NORMALIZE PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void NormalizePlane(float frustum[6][4], int side)
{
	// Here we calculate the magnitude of the normal to the plane (point A B C)
	// Remember that (A, B, C) is that same thing as the normal's (X, Y, Z).
	// To calculate magnitude you use the equation:  magnitude = sqrt( x^2 + y^2 + z^2)
	float magnitude = (float)sqrt( frustum[side][A] * frustum[side][A] + 
								   frustum[side][B] * frustum[side][B] + 
								   frustum[side][C] * frustum[side][C] );

	// Then we divide the plane's values by it's magnitude.
	// This makes it easier to work with.
	frustum[side][A] /= magnitude;
	frustum[side][B] /= magnitude;
	frustum[side][C] /= magnitude;
	frustum[side][D] /= magnitude; 
}


///////////////////////////////// CALCULATE FRUSTUM \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This extracts our frustum from the projection and modelview matrix.
/////
///////////////////////////////// CALCULATE FRUSTUM \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void CFrustum::CalculateFrustum(CVector3 &vPos)
{    
	m_vPos = vPos;
	float   proj[16];								// This will hold our projection matrix
	float   modl[16];								// This will hold our modelview matrix
	float   clip[16];								// This will hold the clipping planes

	// glGetFloatv() is used to extract information about our OpenGL world.
	// Below, we pass in GL_PROJECTION_MATRIX to abstract our projection matrix.
	// It then stores the matrix into an array of [16].
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	// By passing in GL_MODELVIEW_MATRIX, we can abstract our model view matrix.
	// This also stores it in an array of [16].
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	// Now that we have our modelview and projection matrix, if we combine these 2 matrices,
	// it will give us our clipping planes.  To combine 2 matrices, we multiply them.

	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];
	
	// Now we actually want to get the sides of the frustum.  To do this we take
	// the clipping planes we received above and extract the sides from them.

	// This will extract the RIGHT side of the frustum
	m_Frustum[RIGHT][A] = clip[ 3] - clip[ 0];
	m_Frustum[RIGHT][B] = clip[ 7] - clip[ 4];
	m_Frustum[RIGHT][C] = clip[11] - clip[ 8];
	m_Frustum[RIGHT][D] = clip[15] - clip[12];

	// Now that we have a normal (A,B,C) and a distance (D) to the plane,
	// we want to normalize that normal and distance.

	// Normalize the RIGHT side
	NormalizePlane(m_Frustum, RIGHT);

	// This will extract the LEFT side of the frustum
	m_Frustum[LEFT][A] = clip[ 3] + clip[ 0];
	m_Frustum[LEFT][B] = clip[ 7] + clip[ 4];
	m_Frustum[LEFT][C] = clip[11] + clip[ 8];
	m_Frustum[LEFT][D] = clip[15] + clip[12];

	// Normalize the LEFT side
	NormalizePlane(m_Frustum, LEFT);

	// This will extract the BOTTOM side of the frustum
	m_Frustum[BOTTOM][A] = clip[ 3] + clip[ 1];
	m_Frustum[BOTTOM][B] = clip[ 7] + clip[ 5];
	m_Frustum[BOTTOM][C] = clip[11] + clip[ 9];
	m_Frustum[BOTTOM][D] = clip[15] + clip[13];

	// Normalize the BOTTOM side
	NormalizePlane(m_Frustum, BOTTOM);

	// This will extract the TOP side of the frustum
	m_Frustum[TOP][A] = clip[ 3] - clip[ 1];
	m_Frustum[TOP][B] = clip[ 7] - clip[ 5];
	m_Frustum[TOP][C] = clip[11] - clip[ 9];
	m_Frustum[TOP][D] = clip[15] - clip[13];

	// Normalize the TOP side
	NormalizePlane(m_Frustum, TOP);

	// This will extract the BACK side of the frustum
	m_Frustum[BACK][A] = clip[ 3] - clip[ 2];
	m_Frustum[BACK][B] = clip[ 7] - clip[ 6];
	m_Frustum[BACK][C] = clip[11] - clip[10];
	m_Frustum[BACK][D] = clip[15] - clip[14];

	// Normalize the BACK side
	NormalizePlane(m_Frustum, BACK);

	// This will extract the FRONT side of the frustum
	m_Frustum[FRONT][A] = clip[ 3] + clip[ 2];
	m_Frustum[FRONT][B] = clip[ 7] + clip[ 6];
	m_Frustum[FRONT][C] = clip[11] + clip[10];
	m_Frustum[FRONT][D] = clip[15] + clip[14];

	// Normalize the FRONT side
	NormalizePlane(m_Frustum, FRONT);
}

// The code below will allow us to make checks within the frustum.  For example,
// if we want to see if a point, a sphere, or a cube lies inside of the frustum.
// Because all of our planes point INWARDS (The normals are all pointing inside the frustum)
// we then can assume that if a point is in FRONT of all of the planes, it's inside.

///////////////////////////////// POINT IN FRUSTUM \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This determines if a point is inside of the frustum
/////
///////////////////////////////// POINT IN FRUSTUM \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool CFrustum::PointInFrustum( float x, float y, float z )
{
	// If you remember the plane equation (A*x + B*y + C*z + D = 0), then the rest
	// of this code should be quite obvious and easy to figure out yourself.
	// In case don't know the plane equation, it might be a good idea to look
	// at our Plane Collision tutorial at www.GameTutorials.com in OpenGL Tutorials.
	// I will briefly go over it here.  (A,B,C) is the (X,Y,Z) of the normal to the plane.
	// They are the same thing... but just called ABC because you don't want to say:
	// (x*x + y*y + z*z + d = 0).  That would be wrong, so they substitute them.
	// the (x, y, z) in the equation is the point that you are testing.  The D is
	// The distance the plane is from the origin.  The equation ends with "= 0" because
	// that is true when the point (x, y, z) is ON the plane.  When the point is NOT on
	// the plane, it is either a negative number (the point is behind the plane) or a
	// positive number (the point is in front of the plane).  We want to check if the point
	// is in front of the plane, so all we have to do is go through each point and make
	// sure the plane equation goes out to a positive number on each side of the frustum.
	// The result (be it positive or negative) is the distance the point is front the plane.

	// Go through all the sides of the frustum
	for(int i = 0; i < 6; i++ )
	{
		// Calculate the plane equation and check if the point is behind a side of the frustum
		if(m_Frustum[i][A] * x + m_Frustum[i][B] * y + m_Frustum[i][C] * z + m_Frustum[i][D] <= 0)
		{
			// The point was behind a side, so it ISN'T in the frustum
			return false;
		}
	}

	// The point was inside of the frustum (In front of ALL the sides of the frustum)
	return true;
}


///////////////////////////////// SPHERE IN FRUSTUM \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This determines if a sphere is inside of our frustum by it's center and radius.
/////
///////////////////////////////// SPHERE IN FRUSTUM \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool CFrustum::SphereInFrustum( float x, float y, float z, float radius )
{
	// Now this function is almost identical to the PointInFrustum(), except we
	// now have to deal with a radius around the point.  The point is the center of
	// the radius.  So, the point might be outside of the frustum, but it doesn't
	// mean that the rest of the sphere is.  It could be half and half.  So instead of
	// checking if it's less than 0, we need to add on the radius to that.  Say the
	// equation produced -2, which means the center of the sphere is the distance of
	// 2 behind the plane.  Well, what if the radius was 5?  The sphere is still inside,
	// so we would say, if(-2 < -5) then we are outside.  In that case it's false,
	// so we are inside of the frustum, but a distance of 3.  This is reflected below.

	// Go through all the sides of the frustum
	for(int i = 0; i < 6; i++ )	
	{
		// If the center of the sphere is farther away from the plane than the radius
		if( m_Frustum[i][A] * x + m_Frustum[i][B] * y + m_Frustum[i][C] * z + m_Frustum[i][D] <= -radius )
		{
			// The distance was greater than the radius so the sphere is outside of the frustum
			return false;
		}
	}
	
	// The sphere was inside of the frustum!
	return true;
}


///////////////////////////////// CUBE IN FRUSTUM \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This determines if a cube is in or around our frustum by it's center and 1/2 it's length
/////
///////////////////////////////// CUBE IN FRUSTUM \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool CFrustum::CubeInFrustum( float x, float y, float z, float size )
{
	// This test is a bit more work, but not too much more complicated.
	// Basically, what is going on is, that we are given the center of the cube,
	// and half the length.  Think of it like a radius.  Then we checking each point
	// in the cube and seeing if it is inside the frustum.  If a point is found in front
	// of a side, then we skip to the next side.  If we get to a plane that does NOT have
	// a point in front of it, then it will return false.

	// *Note* - This will sometimes say that a cube is inside the frustum when it isn't.
	// This happens when all the corners of the bounding box are not behind any one plane.
	// This is rare and shouldn't effect the overall rendering speed.

	for(int i = 0; i < 6; i++ )
	{
		if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
		   continue;

		// If we get here, it isn't in the frustum
		return false;
	}

	return true;
}

bool CFrustum::CuboidInFrustum( float x, float y, float z, float xLen, float yLen,float zLen)
{
	for(int i = 0; i < 6; i++ )
	{
	//	if(m_Frustum[i][A] * (x) + m_Frustum[i][B] * (y) + m_Frustum[i][C] * (z) + m_Frustum[i][D] > 0)
	//	   continue;
		if(m_Frustum[i][A] * (x - xLen) + m_Frustum[i][B] * (y - yLen) + m_Frustum[i][C] * (z - zLen) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + xLen) + m_Frustum[i][B] * (y - yLen) + m_Frustum[i][C] * (z - zLen) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x - xLen) + m_Frustum[i][B] * (y + yLen) + m_Frustum[i][C] * (z - zLen) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + xLen) + m_Frustum[i][B] * (y + yLen) + m_Frustum[i][C] * (z - zLen) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x - xLen) + m_Frustum[i][B] * (y - yLen) + m_Frustum[i][C] * (z + zLen) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + xLen) + m_Frustum[i][B] * (y - yLen) + m_Frustum[i][C] * (z + zLen) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x - xLen) + m_Frustum[i][B] * (y + yLen) + m_Frustum[i][C] * (z + zLen) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + xLen) + m_Frustum[i][B] * (y + yLen) + m_Frustum[i][C] * (z + zLen) + m_Frustum[i][D] > 0)
		   continue;
		// If we get here, it isn't in the frustum
		return false;
	}
	return true;
}
bool CFrustum::QuadIsVisible(CVector3 *pVert)
{
	CVector3 vNormal = CrossProduct(pVert[1]-pVert[0],pVert[2]-pVert[1]);
	vNormal = -Normalize(vNormal);
	CVector3 vBack = CVector3(m_Frustum[BACK][A],m_Frustum[BACK][B],m_Frustum[BACK][C]);
	vBack = Normalize(vBack);
	if(DotProduct(vNormal,vBack)>cos(22.5/180*3.14159))
		return false;
	return true;
/*	CVector3 vNormal = CrossProduct(pVert[1]-pVert[0],pVert[2]-pVert[1]);
	vNormal = Normalize(vNormal);
	float D = -DotProduct(pVert[0],vNormal);
	CVector3 L0 = CVector3(m_Frustum[0][A],m_Frustum[0][B],m_Frustum[0][C]);
	CVector3 L1 = CVector3(m_Frustum[1][A],m_Frustum[1][B],m_Frustum[1][C]);
	CVector3 L2 = CVector3(m_Frustum[2][A],m_Frustum[2][B],m_Frustum[2][C]);
	CVector3 L3 = CVector3(m_Frustum[3][A],m_Frustum[3][B],m_Frustum[3][C]);

	CVector3 L0_bak = L0;
	L0 = CrossProduct(L0,L1);
	L1 = CrossProduct(L1,L2);
	L2 = CrossProduct(L2,L3);
	L3 = CrossProduct(L3,L0_bak);
	CVector3 vBack = CVector3(m_Frustum[BACK][A],m_Frustum[BACK][B],m_Frustum[BACK][C]);
	if(DotProduct(L0,vBack)<0)
	{
		L0 = -L0;
		L1 = -L1;
		L2 = -L2;
		L3 = -L3;
	}
	float k = -(vNormal.x*vViewPos.x+vNormal.y*vViewPos.y+vNormal.z*vViewPos.z+D);
	float kk = k/(vNormal.x*L0.x+vNormal.y*L0.y+vNormal.z*L0.z);
	CVector3 vInter;
	vInter.x = kk*L0.x+vViewPos.x;
	vInter.y = kk*L0.y+vViewPos.y; 
	vInter.z = kk*L0.z+vViewPos.z;
	if(DotProduct(pVert[0]-vInter,pVert[2]-vInter)<0)
		return true;

	kk = k/(vNormal.x*L1.x+vNormal.y*L1.y+vNormal.z*L1.z);
	vInter.x = kk*L1.x+vViewPos.x;
	vInter.y = kk*L1.y+vViewPos.y; 
	vInter.z = kk*L1.z+vViewPos.z;
	if(DotProduct(pVert[0]-vInter,pVert[2]-vInter)<0)
		return true;

	kk = k/(vNormal.x*L2.x+vNormal.y*L2.y+vNormal.z*L2.z);
	vInter.x = kk*L2.x+vViewPos.x;
	vInter.y = kk*L2.y+vViewPos.y; 
	vInter.z = kk*L2.z+vViewPos.z;
	if(DotProduct(pVert[0]-vInter,pVert[2]-vInter)<0)
		return true;

	kk = k/(vNormal.x*L3.x+vNormal.y*L3.y+vNormal.z*L3.z);
	vInter.x = kk*L3.x+vViewPos.x;
	vInter.y = kk*L3.y+vViewPos.y; 
	vInter.z = kk*L3.z+vViewPos.z;
	if(DotProduct(pVert[0]-vInter,pVert[2]-vInter)<0)
		return true;
	return false;*/
/*	if(DotProduct(vNormal,L0)<0||DotProduct(vNormal,L1)<0||
		DotProduct(vNormal,L2)<0||DotProduct(vNormal,L3)<0)
	{
		return true;
	}
	return false;
*/
}
bool PntInTrigle(CVector3 &vPoint,CVector3 &a,CVector3 &b,CVector3 &c,CVector3 &vNormal)
{
	CVector3 vNormalPer = CrossProduct(b-a,vNormal);
	vNormalPer = Normalize(vNormalPer);
	float D = -DotProduct(a,vNormal);
	// 检查物体是否在过三角形第一条边AB的垂直平面
	if(DotProduct(vNormalPer,c-a)<0)
		vNormalPer = -vNormalPer;
	if(DotProduct(vNormalPer,vPoint)-D<0)
		return false;
	// 检查物体是否在过三角形第一条边BC的垂直平面
	vNormalPer = CrossProduct(c-b,vNormal);
	vNormalPer = Normalize(vNormalPer);
	if(DotProduct(vNormalPer,a-b)<0)
		vNormalPer = -vNormalPer;
	if(DotProduct(vNormalPer,vPoint)-D<0)
		return false;
	// 检查物体是否在过三角形第一条边CA的垂直平面
	vNormalPer = CrossProduct(a-c,vNormal);
	vNormalPer = Normalize(vNormalPer);
	if(DotProduct(vNormalPer,b-c)<0)
		vNormalPer = -vNormalPer;
	if(DotProduct(vNormalPer,vPoint)-D<0)
		return false;
	return true;
}
#define  FLT_MAX 3.402823466e+38F 
#define  FLT_MIN 1.175494351e-38F 

void CalcBoundBox(CVector3 &a,CVector3 &b,CVector3 &c,CVector3 &vCenter,float &xLen,float &yLen,float &zLen)
{
	float xMax = FLT_MIN;
	float xMin = FLT_MAX;
	float yMax = FLT_MIN;
	float yMin = FLT_MAX;
	float zMax = FLT_MIN;
	float zMin = FLT_MAX;
	if(xMax<a.x)
		xMax = a.x;
	if(xMin>a.x)
		xMin = a.x;
	
	if(xMax<b.x)
		xMax = b.x;
	if(xMin>b.x)
		xMin = b.x;
	
	if(xMax<c.x)
		xMax = c.x;
	if(xMin>c.x)
		xMin = c.x;
	
	
	if(yMax<a.y)
		yMax = a.y;
	if(yMin>a.y)
		yMin = a.y;
	
	if(yMax<b.y)
		yMax = b.y;
	if(yMin>b.y)
		yMin = b.y;
	
	if(yMax<c.y)
		yMax = c.y;
	if(yMin>c.y)
		yMin = c.y;
	
	
	if(zMax<a.z)
		zMax = a.z;
	if(zMin>a.z)
		zMin = a.z;
	
	if(zMax<b.z)
		zMax = b.z;
	if(zMin>b.z)
		zMin = b.z;
	
	if(zMax<c.z)
		zMax = c.z;
	if(zMin>c.z)
		zMin = c.z;
	vCenter.x = (xMax + xMin)/2;
	vCenter.y = (yMax + yMin)/2;
	vCenter.z = (zMax + zMin)/2;
	xLen = fabs(xMax-xMin)/2;
	yLen = fabs(yMax-yMin)/2;
	zLen = fabs(zMax-zMin)/2;
}
void CalcBoundBox(CVector3 &a,CVector3 &b,CVector3 &c,CVector3 &d, CVector3 &vCenter,float &xLen,float &yLen,float &zLen)
{
	float xMax = FLT_MIN;
	float xMin = FLT_MAX;
	float yMax = FLT_MIN;
	float yMin = FLT_MAX;
	float zMax = FLT_MIN;
	float zMin = FLT_MAX;
	if(xMax<a.x)
		xMax = a.x;
	if(xMin>a.x)
		xMin = a.x;
	
	if(xMax<b.x)
		xMax = b.x;
	if(xMin>b.x)
		xMin = b.x;
	
	if(xMax<c.x)
		xMax = c.x;
	if(xMin>c.x)
		xMin = c.x;
	
	if(xMax<d.x)
		xMax = d.x;
	if(xMin>d.x)
		xMin = d.x;
//////////////////////////////////////////////	
	if(yMax<a.y)
		yMax = a.y;
	if(yMin>a.y)
		yMin = a.y;
	
	if(yMax<b.y)
		yMax = b.y;
	if(yMin>b.y)
		yMin = b.y;
	
	if(yMax<c.y)
		yMax = c.y;
	if(yMin>c.y)
		yMin = c.y;
	
	if(yMax<d.y)
		yMax = d.y;
	if(yMin>d.y)
		yMin = d.y;
////////////////////////////////////////////////////	
	if(zMax<a.z)
		zMax = a.z;
	if(zMin>a.z)
		zMin = a.z;
	
	if(zMax<b.z)
		zMax = b.z;
	if(zMin>b.z)
		zMin = b.z;
	
	if(zMax<c.z)
		zMax = c.z;
	if(zMin>c.z)
		zMin = c.z;

	if(zMax<d.z)
		zMax = d.z;
	if(zMin>d.z)
		zMin = d.z;
/////////////////////////////////////////////////////
	vCenter.x = (xMax + xMin)/2;
	vCenter.y = (yMax + yMin)/2;
	vCenter.z = (zMax + zMin)/2;
	xLen = fabs(xMax-xMin)/2;
	yLen = fabs(yMax-yMin)/2;
	zLen = fabs(zMax-zMin)/2;
}
bool CFrustum::IntersectQuad(CVector3 &a,CVector3 &b,CVector3 &c,CVector3 &d,CVector3 vInter[])
{
	CVector3 vCenter;
	float xLen,yLen,zLen;
	CalcBoundBox(a,b,c,d,vCenter,xLen,yLen,zLen);
	
	CVector3 vNormal = CrossProduct(b-a,c-b);//三角形的法向量
	CVector3 vBack = CVector3(m_Frustum[BACK][A],m_Frustum[BACK][B],m_Frustum[BACK][C]);
	vBack = Normalize(vBack);
	vNormal = Normalize(vNormal);
	float D = -DotProduct(a,vNormal);//三角形平面到原点的距离
	CVector3 L0 = CVector3(m_Frustum[0][A],m_Frustum[0][B],m_Frustum[0][C]);
	CVector3 L1 = CVector3(m_Frustum[1][A],m_Frustum[1][B],m_Frustum[1][C]);
	CVector3 L2 = CVector3(m_Frustum[2][A],m_Frustum[2][B],m_Frustum[2][C]);
	CVector3 L3 = CVector3(m_Frustum[3][A],m_Frustum[3][B],m_Frustum[3][C]);
	//求视锥体的4条视线
	CVector3 L0_bak = L0;
	L0 = CrossProduct(L0,L1);
	L1 = CrossProduct(L1,L2);
	L2 = CrossProduct(L2,L3);
	L3 = CrossProduct(L3,L0_bak);
	if(DotProduct(L0,vBack)<0)
	{
		L0 = -L0;
		L1 = -L1;
		L2 = -L2;
		L3 = -L3;
	}
	float k = -(vNormal.x*m_vPos.x+vNormal.y*m_vPos.y+vNormal.z*m_vPos.z+D);
	float kk = k/(vNormal.x*L0.x+vNormal.y*L0.y+vNormal.z*L0.z);
//	CVector3 vInter;
	//因为三角形面的3个顶点已经不在视野内,如果此三角形在视野之内,则视锥体的4条射线必定都与三角形面相交
	//只要有一条射线与三角形面不相交,就可断定此三角形面不在视野内
	//视线1与面的交点
	vInter[0].x = kk*L0.x+m_vPos.x;
	vInter[0].y = kk*L0.y+m_vPos.y; 
	vInter[0].z = kk*L0.z+m_vPos.z;
////////////////////////////////////////////////////////////////////////
	//视线2与面的交点
	kk = k/(vNormal.x*L1.x+vNormal.y*L1.y+vNormal.z*L1.z);
	vInter[1].x = kk*L1.x+m_vPos.x;
	vInter[1].y = kk*L1.y+m_vPos.y; 
	vInter[1].z = kk*L1.z+m_vPos.z;
//////////////////////////////////////////////////////////////////////
	//视线3与面的交点
	kk = k/(vNormal.x*L2.x+vNormal.y*L2.y+vNormal.z*L2.z);
	vInter[2].x = kk*L2.x+m_vPos.x;
	vInter[2].y = kk*L2.y+m_vPos.y; 
	vInter[2].z = kk*L2.z+m_vPos.z;
/////////////////////////////////////////////////////////////////////
	//视线4与面的交点
	kk = k/(vNormal.x*L3.x+vNormal.y*L3.y+vNormal.z*L3.z);
	vInter[3].x = kk*L3.x+m_vPos.x;
	vInter[3].y = kk*L3.y+m_vPos.y; 
	vInter[3].z = kk*L3.z+m_vPos.z;
	
	for(int i = 0;i<4;i++)
	{
		if(vInter[i].x>vCenter.x+xLen)
			vInter[i].x = vCenter.x+xLen;
		if(vInter[i].x<vCenter.x-xLen)
			vInter[i].x = vCenter.x-xLen;
		if(vInter[i].y>vCenter.y+yLen)
			vInter[i].y = vCenter.y+yLen;
		if(vInter[i].y<vCenter.y-yLen)
			vInter[i].y = vCenter.y-yLen;
		if(vInter[i].z>vCenter.z+zLen)
			vInter[i].z = vCenter.z+zLen;
		if(vInter[i].z<vCenter.z-zLen)
			vInter[i].z = vCenter.z-zLen;
	}
	return CuboidInFrustum(vCenter.x,vCenter.y,vCenter.z,xLen,yLen,zLen);
}
bool CFrustum::TrigleIsInFrustum(CVector3 &vViewPos,CVector3 &a,CVector3 &b,CVector3 &c)
{
	CVector3 vCenter;
	float xLen,yLen,zLen;
	CalcBoundBox(a,b,c,vCenter,xLen,yLen,zLen);
	//三角形面的3个顶点不在视野内,不能断定此三角形不在视野内
	if(CuboidInFrustum(vCenter.x,vCenter.y,vCenter.z,xLen,yLen,zLen))
		return true;
	return false;//迷茫?????
	CVector3 vNormal = CrossProduct(b-a,c-b);//三角形的法向量
	CVector3 vBack = CVector3(m_Frustum[BACK][A],m_Frustum[BACK][B],m_Frustum[BACK][C]);
	vBack = Normalize(vBack);
	vNormal = Normalize(vNormal);
	float D = -DotProduct(a,vNormal);//三角形平面到原点的距离
	CVector3 L0 = CVector3(m_Frustum[0][A],m_Frustum[0][B],m_Frustum[0][C]);
	CVector3 L1 = CVector3(m_Frustum[1][A],m_Frustum[1][B],m_Frustum[1][C]);
	CVector3 L2 = CVector3(m_Frustum[2][A],m_Frustum[2][B],m_Frustum[2][C]);
	CVector3 L3 = CVector3(m_Frustum[3][A],m_Frustum[3][B],m_Frustum[3][C]);
	//求视锥体的4条视线
	CVector3 L0_bak = L0;
	L0 = CrossProduct(L0,L1);
	L1 = CrossProduct(L1,L2);
	L2 = CrossProduct(L2,L3);
	L3 = CrossProduct(L3,L0_bak);
	if(DotProduct(L0,vBack)<0)
	{
		L0 = -L0;
		L1 = -L1;
		L2 = -L2;
		L3 = -L3;
	}
	float k = -(vNormal.x*vViewPos.x+vNormal.y*vViewPos.y+vNormal.z*vViewPos.z+D);
	float kk = k/(vNormal.x*L0.x+vNormal.y*L0.y+vNormal.z*L0.z);
	CVector3 vInter;
	//因为三角形面的3个顶点已经不在视野内,如果此三角形在视野之内,则视锥体的4条射线必定都与三角形面相交
	//只要有一条射线与三角形面不相交,就可断定此三角形面不在视野内
	//视线1与面的交点
	vInter.x = kk*L0.x+vViewPos.x;
	vInter.y = kk*L0.y+vViewPos.y; 
	vInter.z = kk*L0.z+vViewPos.z;
	if(!PntInTrigle(vInter,a,b,c,vNormal))
		return false;
////////////////////////////////////////////////////////////////////////
	//视线2与面的交点
	kk = k/(vNormal.x*L1.x+vNormal.y*L1.y+vNormal.z*L1.z);
	vInter.x = kk*L1.x+vViewPos.x;
	vInter.y = kk*L1.y+vViewPos.y; 
	vInter.z = kk*L1.z+vViewPos.z;
	if(!PntInTrigle(vInter,a,b,c,vNormal))
		return false;
//////////////////////////////////////////////////////////////////////
	//视线3与面的交点
	kk = k/(vNormal.x*L2.x+vNormal.y*L2.y+vNormal.z*L2.z);
	vInter.x = kk*L2.x+vViewPos.x;
	vInter.y = kk*L2.y+vViewPos.y; 
	vInter.z = kk*L2.z+vViewPos.z;
	if(!PntInTrigle(vInter,a,b,c,vNormal))
		return false;
/////////////////////////////////////////////////////////////////////
	//视线4与面的交点
	kk = k/(vNormal.x*L3.x+vNormal.y*L3.y+vNormal.z*L3.z);
	vInter.x = kk*L3.x+vViewPos.x;
	vInter.y = kk*L3.y+vViewPos.y; 
	vInter.z = kk*L3.z+vViewPos.z;
	if(!PntInTrigle(vInter,a,b,c,vNormal))
		return false;
//	if(DotProduct(vNormal,L0)<0&&DotProduct(vNormal,L1)<0&&
//		DotProduct(vNormal,L2)<0&&DotProduct(vNormal,L3)<0)
//		return false;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// WOZZERS!  That seemed like an incredible amount to look at, but if you break it
// down, it's not.  Frustum culling is a VERY useful thing when it comes to 3D.
// If you want a large world, there is no way you are going to send it down the
// 3D pipeline every frame and let OpenGL take care of it for you.  That would
// give you a 0.001 frame rate.  If you hit '+' and bring the sphere count up to
// 1000, then take off culling, you will see the HUGE difference it makes.  
// Also, you wouldn't really be rendering 1000 spheres.  You would most likely
// use the sphere code for larger objects.  Let me explain.  Say you have a bunch
// of objects, well... all you need to do is give the objects a radius, and then
// test that radius against the frustum.  If that sphere is in the frustum, then you
// render that object.  Also, you won't be rendering a high poly sphere so it won't
// be so slow.  This goes for bounding box's too (Cubes).  If you don't want to
// do a cube, it is really easy to convert the code for rectangles.  Just pass in
// a width and height, instead of just a length.  Remember, it's HALF the length of
// the cube, not the full length.  So it would be half the width and height for a rect.
// 
// This is a perfect starter for an octree tutorial.  Wrap you head around the concepts
// here and then see if you can apply this to making an octree.  Hopefully we will have
// a tutorial up and running for this subject soon.  Once you have frustum culling,
// the next step is getting space partitioning.  Either it being a BSP tree of an Octree.
// 
// Let's go over a brief overview of the things we learned here:
//
// 1) First we need to abstract the frustum from OpenGL.  To do that we need the
//    projection and modelview matrix.  To get the projection matrix we use:
//
//			glGetFloatv( GL_PROJECTION_MATRIX, /* An Array of 16 floats */ );
//    Then, to get the modelview matrix we use:
//
//			glGetFloatv( GL_MODELVIEW_MATRIX, /* An Array of 16 floats */ );
//    
//	  These 2 functions gives us an array of 16 floats (The matrix).
//
// 2) Next, we need to combine these 2 matrices.  We do that by matrix multiplication.
//
// 3) Now that we have the 2 matrixes combined, we can abstract the sides of the frustum.
//    This will give us the normal and the distance from the plane to the origin (ABC and D).
//
// 4) After abstracting a side, we want to normalize the plane data.  (A B C and D).
//
// 5) Now we have our frustum, and we can check points against it using the plane equation.
//    Once again, the plane equation (A*x + B*y + C*z + D = 0) says that if, point (X,Y,Z)
//    times the normal of the plane (A,B,C), plus the distance of the plane from origin,
//    will equal 0 if the point (X, Y, Z) lies on that plane.  If it is behind the plane
//    it will be a negative distance, if it's in front of the plane (the way the normal is facing)
//    it will be a positive number.
//
//
// If you need more help on the plane equation and why this works, download our
// Ray Plane Intersection Tutorial at www.GameTutorials.com.
//
// That's pretty much it with frustums.  There is a lot more we could talk about, but
// I don't want to complicate this tutorial more than I already have.
//
// I want to thank Mark Morley for his tutorial on frustum culling.  Most of everything I got
// here comes from his teaching.  If you want more in-depth, visit his tutorial at:
//
// http://www.markmorley.com/opengl/frustumculling.html
//
// Good luck!
//
//
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
//
