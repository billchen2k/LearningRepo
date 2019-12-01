// Frustum.h: interface for the CFrustum class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRUSTUM_H__55BE2796_F699_42C5_907D_728962C28269__INCLUDED_)
#define AFX_FRUSTUM_H__55BE2796_F699_42C5_907D_728962C28269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//class CTerrain;
#include "gamehead.h"
#include "vector.h"
enum FrustumSide
{
	RIGHT	= 2,		// The RIGHT side of the frustum
	LEFT	= 0,		// The LEFT	 side of the frustum
	BOTTOM	= 3,		// The BOTTOM side of the frustum
	TOP		= 1,		// The TOP side of the frustum
	BACK	= 4,		// The BACK	side of the frustum
	FRONT	= 5			// The FRONT side of the frustum
}; 

// Like above, instead of saying a number for the ABC and D of the plane, we
// want to be more descriptive.
enum PlaneData
{
	A = 0,				// The X value of the plane's normal
	B = 1,				// The Y value of the plane's normal
	C = 2,				// The Z value of the plane's normal
	D = 3				// The distance the plane is from the origin
};
class CFrustum  
{
	friend class CTerrain;
	friend class CPortal;
public:

	// Call this every time the camera moves to update the frustum
	void CalculateFrustum(CVector3 &vPos);

	// This takes a 3D point and returns TRUE if it's inside of the frustum
	bool PointInFrustum(float x, float y, float z);

	// This takes a 3D point and a radius and returns TRUE if the sphere is inside of the frustum
	bool SphereInFrustum(float x, float y, float z, float radius);

	// This takes the center and half the length of the cube.
	bool CubeInFrustum( float x, float y, float z, float size );

	bool CuboidInFrustum( float x, float y, float z, float xLen, float yLen,float zLen);
	bool QuadIsVisible(CVector3 *pVert);
	bool TrigleIsInFrustum(CVector3 &vViewPos,CVector3 &a,CVector3 &b,CVector3 &c);
	bool IntersectQuad(CVector3 &a,CVector3 &b,CVector3 &c,CVector3 &d,CVector3 vInter[]);

public:
	// This holds the A B C and D values for each side of our frustum.
	float m_Frustum[6][4];
	static CVector3 m_vPos;
public:
	CFrustum();
	virtual ~CFrustum();

};

#endif // !defined(AFX_FRUSTUM_H__55BE2796_F699_42C5_907D_728962C28269__INCLUDED_)
