#if !defined(AFX_GAMEHEAD_H__A7C41EA3_DB80_49DA_9A84_72E6251F9A21__INCLUDED_)
#define AFX_GAMEHEAD_H__A7C41EA3_DB80_49DA_9A84_72E6251F9A21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
#include <memory.h>
#include <stdio.h>
#include <math.h>
#include <gl\gl.h>			//OpenGL header file
#include <gl\glu.h>			//The OpenGL Glu header file
#include "glaux.h"	// Header File For The Glaux Library
#pragma comment(lib, "OpenGL32.lib")//Search for the OpenGL32 library at compile time
#pragma comment(lib, "Glu32.lib")	//Search for the Glu32 library at compile time
#pragma comment(lib, "GLaux.lib")
#pragma warning( disable :  4244 4305 )  // Disable warning messages#pragma disable(C4244)
typedef void (APIENTRY * PFNGLFOGCOORDFEXTPROC) (GLfloat coord);
extern PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;
#define GL_FOG_COORDINATE_SOURCE_EXT			0x8450
#define GL_FOG_COORDINATE_EXT					0x8451

// These are for our multitexture defines
#define GL_TEXTURE0_ARB                     0x84C0
#define GL_TEXTURE1_ARB                     0x84C1

#define GL_COMBINE_ARB						0x8570
#define GL_RGB_SCALE_ARB					0x8573

// Here are the multitexture function prototypes
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum target);

// Here we extern our function pointers for multitexturing capabilities
extern PFNGLMULTITEXCOORD2FARBPROC			glMultiTexCoord2fARB;
extern PFNGLACTIVETEXTUREARBPROC			glActiveTextureARB;

#endif // !defined(AFX_GAMEWND_H__A7C41EA3_DB80_49DA_9A84_72E6251F9A21__INCLUDED_)
