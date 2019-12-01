// Scene.cpp: implementation of the CScene class.
//
//////////////////////////////////////////////////////////////////////

#include "Scene.h"
#include "gamehead.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;
 PFNGLMULTITEXCOORD2FARBPROC			glMultiTexCoord2fARB;
 PFNGLACTIVETEXTUREARBPROC			glActiveTextureARB;
char g_strText[10][255];
CScene::CScene()
{
	for(int i = 0;i<10;i++)
	{
		g_strText[i][0] = '\0';
	}
}

CScene::~CScene()
{

}



void CScene::Init()
{
	m_Camera.PositionCamera(1000, 300 ,1000,   5000, 553, 5000,   0, 1, 0);
	m_3ds.Init("DemoHouse.3ds");
}	

void CScene::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	glColor3f(1.0,1.0,1.0);
	m_Camera.Look();	
	//m_Frustum.CalculateFrustum(m_Camera.GetPos());
	m_3ds.Draw();
}



