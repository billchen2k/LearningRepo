/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing This Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */

//HINSTANCE	hInstance;		// Holds The Instance Of The Application
#include "gamewnd.h"
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	CGameWnd gameWnd;
	// Create Our OpenGL Window
	if (!gameWnd.CreateGLWindow("My Game",800,600,16,true))
		return 0;									// Quit If Window Was Not Created
	while(1)									// Loop That Runs While bDone=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
				break;						// If So bDone=TRUE
			TranslateMessage(&msg);				// Translate The Message
			DispatchMessage(&msg);				// Dispatch The Message	
		}
		else										// If There Are No Messages
		{
			if(gameWnd.bActive())
			{
				gameWnd.UpdateKeyMouse();
			//	OutputDebugString("bActive\n");
				gameWnd.DrawGLScene();
				::SwapBuffers(wglGetCurrentDC());
			//	gameWnd.SwapBuffers();					// Swap Buffers (Double Buffering)
			//	::SetBkMode(::GetDC(gameWnd.m_hWnd), TRANSPARENT );
			//	::TextOut(::GetDC(gameWnd.m_hWnd),5,5,"11111",5);

			}
			else
			{
				ShowWindow(gameWnd.m_hWnd,SW_SHOWMINIMIZED);
				WaitMessage();
			}
		}
	}
	gameWnd.KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}

