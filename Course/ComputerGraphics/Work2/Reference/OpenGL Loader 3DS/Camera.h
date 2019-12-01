#ifndef _CAMERA_H
#define _CAMERA_H
// This is our basic 3D point/vector class

// This was created to allow you to use this camera code in your projects
// without having to cut and paste code.  This file and camera.cpp should be
// added to your project.

// This is our camera class
#include "math.h"
#include "vector.h"

class CCamera 
{
friend class CPortal;
public:
	// Our camera constructor
	CCamera();	
//	void SetCText(CText *pText){m_pText = pText;m_nTextID = pText->AddText(0,0,0,"");};
/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	// These are are data access functions for our camera's private data
	CVector3 Position() {	return m_vPosition;		}
	CVector3 View()		{	return m_vView;			}
	CVector3 UpVector() {	return m_vUpVector;		}
	CVector3 Strafe()	{	return m_vStrafe;		}

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	
	// This changes the position, view, and up vector of the camera.
	// This is primarily used for initialization
	void PositionCamera(float positionX, float positionY, float positionZ,
			 		    float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ);

	// This rotates the camera's view around the position depending on the values passed in.
	void RotateView(float angle, float X, float Y, float Z);

	// This moves the camera's view by the mouse movements (First person view)
	void SetViewByMouse(); 

	// This rotates the camera around a point (I.E. your character).
	void RotateAroundPoint(CVector3 vCenter, float X, float Y, float Z);


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	// This strafes the camera left or right depending on the speed (+/-) 
	void StrafeCamera(float speed);

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


	// This will move the camera forward or backward depending on the speed
	void MoveCamera(float speed);

	// This checks for keyboard movement
	void CheckForMovement();


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

	// This updates the camera's view and other data (Should be called each frame)
	void Update();

	// This uses gluLookAt() to tell OpenGL where to look
	void Look();
	
	CVector3 GetPos(){return m_vPosition;};

	CVector3 GetView(){return m_vView;};
private:

	// The camera's position
	CVector3 m_vPosition;					

	// The camera's view
	CVector3 m_vView;						

	// The camera's up vector
	CVector3 m_vUpVector;		
	
	// The camera's strafe vector
	CVector3 m_vStrafe;						

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

};


#endif


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// This file contains the prototype for our camera class.  
//
// We add a few more functions to our CCamera class, along with
// some measly data access functions for our now private member variables.
//
// 
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
//