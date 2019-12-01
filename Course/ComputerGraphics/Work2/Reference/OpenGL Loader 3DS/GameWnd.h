// GameWnd.h: interface for the CGameWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEWND_H__A7C41EA3_DB80_49DA_9A84_72E6251F9A21__INCLUDED_)
#define AFX_GAMEWND_H__A7C41EA3_DB80_49DA_9A84_72E6251F9A21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "gamehead.h"
#include "texture.h"
#include "scene.h"
class CGameWnd 
{
	CScene		m_Scene;
	HDC			m_hDC;		// Private GDI Device Context
	HGLRC		m_hRC;		// Permanent Rendering Context	
	bool		m_bFullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default
	static bool	m_bActive;		// Window Active Flag Set To TRUE By Default
public:
	static HWND		m_hWnd;		// Holds Our Window Handle
public:
	bool bActive(){return m_bActive;};
	void UpdateKeyMouse(){m_Scene.UpdateKeyMouse();};
public:
	BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);
	GLvoid KillGLWindow(GLvoid);
	int DrawGLScene(GLvoid);	
private:
	int InitGL(GLvoid);
	static LRESULT  CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM	wParam,LPARAM lParam);
	static GLvoid  ReSizeGLScene(GLsizei width, GLsizei height);
public:
	CGameWnd();
	virtual ~CGameWnd();
};

#endif // !defined(AFX_GAMEWND_H__A7C41EA3_DB80_49DA_9A84_72E6251F9A21__INCLUDED_)
