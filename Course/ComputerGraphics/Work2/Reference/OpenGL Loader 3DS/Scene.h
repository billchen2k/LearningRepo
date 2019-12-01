// Scene.h: interface for the CScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENE_H__B2A48E92_25AA_4FBB_B123_D0BBA69EFDEB__INCLUDED_)
#define AFX_SCENE_H__B2A48E92_25AA_4FBB_B123_D0BBA69EFDEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "camera.h"
#include "Frustum.h"
#include "Vector.h"

#include "3ds.h"
class CScene  
{
	CCamera		m_Camera;
//	CFrustum	m_Frustum;
	C3DS		m_3ds;
public:
	void UpdateKeyMouse(){m_Camera.Update();};
	void Draw();
	void Init();
	CScene();
	virtual ~CScene();

};

#endif // !defined(AFX_SCENE_H__B2A48E92_25AA_4FBB_B123_D0BBA69EFDEB__INCLUDED_)
