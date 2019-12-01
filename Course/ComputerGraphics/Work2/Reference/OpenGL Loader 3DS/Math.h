//------------------------------------------------------------------//
//- class VECTOR3D -------------------------------------------------//
//------------------------------------------------------------------//
//- A class for all three dimensional vectors.  This will have some-//
//- very nice features so that we can add/multiply/subtract/divide -//
//- vectors together now! (Also used for vertices)				   -//
//------------------------------------------------------------------//
#include "gamehead.h"



//------------------------------------------------------------------//
//- class VECTOR3D -------------------------------------------------//
//------------------------------------------------------------------//
//- A class for all three dimensional vectors.  This will have some-//
//- very nice features so that we can add/multiply/subtract/divide -//
//- vectors together now! (Also used for vertices)				   -//
//------------------------------------------------------------------//
class CVertex
	{
	public:
		float vertex[3];

	CVertex inline operator+ (const CVertex &v);
	CVertex inline operator- (const CVertex &v);
	CVertex inline operator* (const float scalar);
	CVertex inline operator* (const CVertex &v);
	CVertex inline operator/ (const CVertex &v);

	void SendToOGL(void);

	CVertex()
		{	memset(vertex, 0, sizeof(float[3]));	}
	CVertex(float x, float y, float z);
	};

//------------------------------------------------------------------//
//- class VECTOR3D -------------------------------------------------//
//------------------------------------------------------------------//
//- A class for 4x4 matrices.									   -//
//------------------------------------------------------------------//
class CMatrix44
	{
	public:
		float matrix[16];

	void LoadZero(void);
	void LoadIdentity(void);

	friend CMatrix44 operator+ (const CMatrix44 &m1, const CMatrix44 &m2);
	friend CMatrix44 operator- (const CMatrix44 &m1, const CMatrix44 &m2);
	friend CMatrix44 operator* (const CMatrix44 &m1, const float scalar);
	friend CMatrix44 operator* (const CMatrix44 &m1, const CMatrix44 &m2);

	CMatrix44()
		{	memset(matrix, 0, sizeof(float[16]));	}
	};


//------------------------------------------------------------------//
//- class SHINING3D ------------------------------------------------//
//------------------------------------------------------------------//
//- The main graphics/window class.  Has functions for creating a  -//
//- window, and various other stuff.							   -//
//------------------------------------------------------------------//