//==================================================================//
//==================================================================//
//= Math.cpp =======================================================//
//==================================================================//
//= Original coder: Trent Polack (ShiningKnight) ===================//
//==================================================================//
//==================================================================//


#include "math.h"
#include <math.h>
#include "vector.h"
//#define SQUARE(number) (number*number)

//------------------------------------------------------------------//
//------------------------------------------------------------------//
//- DEFINITIONS ----------------------------------------------------//
//------------------------------------------------------------------//
//------------------------------------------------------------------//

//------------------------------------------------------------------//
//- GLint Random(GLint, GLint) -------------------------------------//
//------------------------------------------------------------------//
//- Description: Returns a random number from the range of numbers -//
//-              that you supply.								   -//
//------------------------------------------------------------------//
//GLint Random(GLint min, GLint max) 
//	{	return (rand()%(max-min+1))+min;	}



//------------------------------------------------------------------//
//- void ComputeNormal(CVector3*, CVector3*, CVector3*) ------------------//
//------------------------------------------------------------------//
//- Description: Sends a surface normal (composed of 3 vectors), to-//
//-              OpenGL.										   -//
//------------------------------------------------------------------//

//------------------------------------------------------------------//
//- CVector3(float, float, float) ------------------------------------//
//------------------------------------------------------------------//
//- Description: The constructor that intializes the parts of the  -//
//-				 vector to your specifications.					   -//
//------------------------------------------------------------------//




//------------------------------------------------------------------//
//- inline CVector3 CVector3::operator* (CVector3) -----------------------//
//------------------------------------------------------------------//
//- Description: Overloading the * operator.  But this time it is  -//
//-				 for vector by vector multiplication.			   -//
//------------------------------------------------------------------//


//------------------------------------------------------------------//
//- inline CVector3 CVector3::operator/ (CVector3) -----------------------//
//------------------------------------------------------------------//
//- Description: Overloading the / operator, allowing you to divide-//
//-				 one vector to another.							   -//
//------------------------------------------------------------------//



//------------------------------------------------------------------//
//- CVertex(float, float, float) ------------------------------------//
//------------------------------------------------------------------//
//- Description: The constructor that intializes the parts of the  -//
//-				 vector to your specifications.					   -//
//------------------------------------------------------------------//
CVertex::
	CVertex(float x, float y, float z)
	{
	vertex[0]=x;
	vertex[1]=y;
	vertex[2]=z;
	}

//------------------------------------------------------------------//
//- void CVertex::SendToOGL(void) -----------------------------------//
//------------------------------------------------------------------//
//- Description: This function sends the class's vertex array to   -//
//-				 OpenGL.										   -//
//------------------------------------------------------------------//
void CVertex::
	SendToOGL(void)
	{	glVertex3fv(vertex);	}

//------------------------------------------------------------------//
//- inline CVertex CVertex::operator+ (CVertex) -----------------------//
//------------------------------------------------------------------//
//- Description: Overloading the + operator, allowing you to add   -//
//-				 one vertex to another, with some nice looking     -//
//-				 code.											   -//
//------------------------------------------------------------------//
inline CVertex CVertex::
	operator+ (const CVertex &v)
	{
	CVertex result(0.0f, 0.0f, 0.0f);

	result.vertex[0]= vertex[0] + v.vertex[0];
	result.vertex[1]= vertex[1] + v.vertex[1];
	result.vertex[2]= vertex[2] + v.vertex[2];

	return result;
	}

//------------------------------------------------------------------//
//- inline CVertex CVertex::operator- (CVertex) -----------------------//
//------------------------------------------------------------------//
//- Description: Overloading the - operator, allowing you to	   -//
//-				 subtract one vertex to another, with some nice	   -//
//-				 looking code.									   -//
//------------------------------------------------------------------//
inline CVertex CVertex::
	operator- (const CVertex &v)
	{
	CVertex result(0.0f, 0.0f, 0.0f);

	result.vertex[0]= vertex[0] - v.vertex[0];
	result.vertex[1]= vertex[1] - v.vertex[1];
	result.vertex[2]= vertex[2] - v.vertex[2];

	return result;
	}


//------------------------------------------------------------------//
//- inline CVector3 CVector3::operator* (float) ------------------------//
//------------------------------------------------------------------//
//- Description: Overloading the * operator, this allows you to    -//
//-				 multiply a every component of a vertex by a scalar-//
//-				 (single value).								   -//
//------------------------------------------------------------------//
inline CVertex CVertex::
	operator* (const float scalar)
	{
	CVertex result(0.0f, 0.0f, 0.0f);

	result.vertex[0]= vertex[0] * scalar;
	result.vertex[1]= vertex[1] * scalar;
	result.vertex[2]= vertex[2] * scalar;

	return result;
	}

//------------------------------------------------------------------//
//- inline CVertex CVertex::operator* (CVertex) -----------------------//
//------------------------------------------------------------------//
//- Description: Overloading the * operator.  But this time it is  -//
//-				 for vertex by vertex multiplication.			   -//
//------------------------------------------------------------------//
inline CVertex CVertex::
	operator* (const CVertex &v)
	{
	CVertex result(0.0f, 0.0f, 0.0f);

	result.vertex[0]= vertex[0] * v.vertex[0];
	result.vertex[1]= vertex[1] * v.vertex[1];
	result.vertex[2]= vertex[2] * v.vertex[2];

	return result;
	}

//------------------------------------------------------------------//
//- inline CVertex CVertex::operator/ (CVertex) -----------------------//
//------------------------------------------------------------------//
//- Description: Overloading the / operator, allowing you to divide-//
//-				 one vertex to another.							   -//
//------------------------------------------------------------------//
inline CVertex CVertex::
	operator/ (const CVertex &v)
	{
	CVertex result(0.0f, 0.0f, 0.0f);

	result.vertex[0]= vertex[0] / v.vertex[0];
	result.vertex[1]= vertex[1] / v.vertex[1];
	result.vertex[2]= vertex[2] / v.vertex[2];

	return result;
	}


//------------------------------------------------------------------//
//- void CMatrix44::LoadIdentity(void) -----------------------------//
//------------------------------------------------------------------//
//- Description: Sets the current matrix to the zero matrix.	   -//
//-				 Zero matrix: | 0  0  0  0 |					   -//
//-							  | 0  0  0  0 |					   -//
//-							  | 0  0  0  0 |					   -//
//-							  | 0  0  0  0 |					   -//
//------------------------------------------------------------------//
//- Sample use:													   -//
//-             matrix.ZeroIdentity();							   -//
//------------------------------------------------------------------//
void CMatrix44::
	LoadZero(void)
	{
	int loop;

	for(loop=0; loop<16; loop++)
		matrix[loop]=0.0f;
	}

//------------------------------------------------------------------//
//- void CMatrix44::LoadIdentity(void) -----------------------------//
//------------------------------------------------------------------//
//- Description: Sets the current matrix to the identity matrix.   -//
//-				 Identity matrix: | 1  0  0  0 |				   -//
//-								  | 0  1  0  0 |				   -//
//-								  | 0  0  1  0 |				   -//
//-								  | 0  0  0  1 |				   -//
//------------------------------------------------------------------//
//- Sample use:													   -//
//-             matrix.LoadIdentity();							   -//
//------------------------------------------------------------------//
void CMatrix44::
	LoadIdentity(void)
	{
	matrix[0] =1.0f; matrix[1] =0.0f; matrix[2] =0.0f; matrix[3] =0.0f;
	matrix[4] =0.0f; matrix[5] =1.0f; matrix[6] =0.0f; matrix[7] =0.0f;
	matrix[8] =0.0f; matrix[9] =0.0f; matrix[10]=1.0f; matrix[11]=0.0f;
	matrix[12]=0.0f; matrix[13]=0.0f; matrix[14]=0.0f; matrix[15]=1.0f;
	}

//------------------------------------------------------------------//
//- CMatrix44 operator+ (CMatrix44, CMatrix44) ---------------------//
//------------------------------------------------------------------//
//- Description: Overloading the + operator.  This adds the        -//
//-				 contents of one matrix to another, and returns the-//
//-				 results.										   -//
//------------------------------------------------------------------//
//- Sample use:													   -//
//-					result= matrix1+matrix2;					   -//
//------------------------------------------------------------------//
CMatrix44 operator+ (const CMatrix44 &m1, const CMatrix44 &m2)
	{
	CMatrix44 result;

	result.matrix[0]= m1.matrix[0]+m2.matrix[0];
	result.matrix[1]= m1.matrix[1]+m2.matrix[1];
	result.matrix[2]= m1.matrix[2]+m2.matrix[2];
	result.matrix[3]= m1.matrix[3]+m2.matrix[3];
	result.matrix[4]= m1.matrix[4]+m2.matrix[4];
	result.matrix[5]= m1.matrix[5]+m2.matrix[5];
	result.matrix[6]= m1.matrix[6]+m2.matrix[6];
	result.matrix[7]= m1.matrix[7]+m2.matrix[7];
	result.matrix[8]= m1.matrix[8]+m2.matrix[8];
	result.matrix[9]= m1.matrix[9]+m2.matrix[9];
	result.matrix[10]=m1.matrix[10]+m2.matrix[10];
	result.matrix[11]=m1.matrix[11]+m2.matrix[11];
	result.matrix[12]=m1.matrix[12]+m2.matrix[12];
	result.matrix[13]=m1.matrix[13]+m2.matrix[13];
	result.matrix[14]=m1.matrix[14]+m2.matrix[14];
	result.matrix[15]=m1.matrix[15]+m2.matrix[15];

	return result;
	}

//------------------------------------------------------------------//
//- CMatrix44 operator- (CMatrix44, CMatrix44) ---------------------//
//------------------------------------------------------------------//
//- Description: Overloading the - operator.  This subtracts the   -//
//-				 contents of one matrix to another, and returns the-//
//-				 results.										   -//
//------------------------------------------------------------------//
//- Sample use:													   -//
//-					result= matrix1-matrix2;					   -//
//------------------------------------------------------------------//
CMatrix44 operator- (const CMatrix44 &m1, const CMatrix44 &m2)
	{
	CMatrix44 result;

	result.matrix[0]= m1.matrix[0]-m2.matrix[0];
	result.matrix[1]= m1.matrix[1]-m2.matrix[1];
	result.matrix[2]= m1.matrix[2]-m2.matrix[2];
	result.matrix[3]= m1.matrix[3]-m2.matrix[3];
	result.matrix[4]= m1.matrix[4]-m2.matrix[4];
	result.matrix[5]= m1.matrix[5]-m2.matrix[5];
	result.matrix[6]= m1.matrix[6]-m2.matrix[6];
	result.matrix[7]= m1.matrix[7]-m2.matrix[7];
	result.matrix[8]= m1.matrix[8]-m2.matrix[8];
	result.matrix[9]= m1.matrix[9]-m2.matrix[9];
	result.matrix[10]=m1.matrix[10]-m2.matrix[10];
	result.matrix[11]=m1.matrix[11]-m2.matrix[11];
	result.matrix[12]=m1.matrix[12]-m2.matrix[12];
	result.matrix[13]=m1.matrix[13]-m2.matrix[13];
	result.matrix[14]=m1.matrix[14]-m2.matrix[14];
	result.matrix[15]=m1.matrix[15]-m2.matrix[15];

	return result;
	}

//------------------------------------------------------------------//
//- CMatrix44 operator* (CMatrix44, float) -------------------------//
//------------------------------------------------------------------//
//- Description: Overloading the * operator.  This is for when you -//
//-				 want to multiply every component of a matrix by a -//
//-				 a scalar.										   -//
//------------------------------------------------------------------//
//- Sample use:													   -//
//-					result= matrix1*2;							   -//
//------------------------------------------------------------------//
CMatrix44 operator* (const CMatrix44 &m1, const float scalar)
	{
	CMatrix44 result;

	result.matrix[0]= m1.matrix[0]*scalar;
	result.matrix[1]= m1.matrix[1]*scalar;
	result.matrix[2]= m1.matrix[2]*scalar;
	result.matrix[3]= m1.matrix[3]*scalar;
	result.matrix[4]= m1.matrix[4]*scalar;
	result.matrix[5]= m1.matrix[5]*scalar;
	result.matrix[6]= m1.matrix[6]*scalar;
	result.matrix[7]= m1.matrix[7]*scalar;
	result.matrix[8]= m1.matrix[8]*scalar;
	result.matrix[9]= m1.matrix[9]*scalar;
	result.matrix[10]=m1.matrix[10]*scalar;
	result.matrix[11]=m1.matrix[11]*scalar;
	result.matrix[12]=m1.matrix[12]*scalar;
	result.matrix[13]=m1.matrix[13]*scalar;
	result.matrix[14]=m1.matrix[14]*scalar;
	result.matrix[15]=m1.matrix[15]*scalar;

	return result;
	}

//------------------------------------------------------------------//
//- CMatrix44 operator* (CMatrix44, CMatrix44) ---------------------//
//------------------------------------------------------------------//
//- Description: Overloading the * operator.  This does the 'real' -//
//-				 matrix multiplication, and is pretty slow, though -//
//-				 not nearly as slow as the division operation      -//
//-				 though.										   -//
//------------------------------------------------------------------//
//- Sample use:													   -//
//-					result= matrix1*matrix2;					   -//
//------------------------------------------------------------------//
CMatrix44 operator* (const CMatrix44 &m1, const CMatrix44 &m2)
	{
	CMatrix44 result;

	result.matrix[0]= (m1.matrix[0]*m2.matrix[0])+(m1.matrix[4]*m2.matrix[1])+(m1.matrix[8]*m2.matrix[2])+(m1.matrix[12]*m2.matrix[3]);
	result.matrix[4]= (m1.matrix[0]*m2.matrix[4])+(m1.matrix[4]*m2.matrix[5])+(m1.matrix[8]*m2.matrix[6])+(m1.matrix[12]*m2.matrix[7]);
	result.matrix[8]= (m1.matrix[0]*m2.matrix[8])+(m1.matrix[4]*m2.matrix[9])+(m1.matrix[8]*m2.matrix[10])+(m1.matrix[12]*m2.matrix[11]);
	result.matrix[12]= (m1.matrix[0]*m2.matrix[12])+(m1.matrix[4]*m2.matrix[13])+(m1.matrix[8]*m2.matrix[14])+(m1.matrix[12]*m2.matrix[15]);
	
	result.matrix[1]= (m1.matrix[1]*m2.matrix[0])+(m1.matrix[5]*m2.matrix[1])+(m1.matrix[9]*m2.matrix[2])+(m1.matrix[13]*m2.matrix[3]);
	result.matrix[5]= (m1.matrix[1]*m2.matrix[4])+(m1.matrix[5]*m2.matrix[5])+(m1.matrix[9]*m2.matrix[6])+(m1.matrix[13]*m2.matrix[7]);
	result.matrix[9]= (m1.matrix[1]*m2.matrix[8])+(m1.matrix[5]*m2.matrix[9])+(m1.matrix[9]*m2.matrix[10])+(m1.matrix[13]*m2.matrix[11]);
	result.matrix[13]= (m1.matrix[1]*m2.matrix[12])+(m1.matrix[5]*m2.matrix[13])+(m1.matrix[9]*m2.matrix[14])+(m1.matrix[13]*m2.matrix[15]);

	result.matrix[2]= (m1.matrix[2]*m2.matrix[0])+(m1.matrix[6]*m2.matrix[1])+(m1.matrix[10]*m2.matrix[2])+(m1.matrix[14]*m2.matrix[3]);
	result.matrix[6]= (m1.matrix[2]*m2.matrix[4])+(m1.matrix[6]*m2.matrix[5])+(m1.matrix[10]*m2.matrix[6])+(m1.matrix[14]*m2.matrix[7]);
	result.matrix[10]= (m1.matrix[2]*m2.matrix[8])+(m1.matrix[6]*m2.matrix[9])+(m1.matrix[10]*m2.matrix[10])+(m1.matrix[14]*m2.matrix[11]);
	result.matrix[14]= (m1.matrix[2]*m2.matrix[12])+(m1.matrix[6]*m2.matrix[13])+(m1.matrix[10]*m2.matrix[14])+(m1.matrix[14]*m2.matrix[15]);

	result.matrix[3]= (m1.matrix[3]*m2.matrix[0])+(m1.matrix[7]*m2.matrix[1])+(m1.matrix[11]*m2.matrix[2])+(m1.matrix[15]*m2.matrix[3]);
	result.matrix[7]= (m1.matrix[3]*m2.matrix[4])+(m1.matrix[7]*m2.matrix[5])+(m1.matrix[11]*m2.matrix[6])+(m1.matrix[15]*m2.matrix[7]);
	result.matrix[11]= (m1.matrix[3]*m2.matrix[8])+(m1.matrix[7]*m2.matrix[9])+(m1.matrix[11]*m2.matrix[10])+(m1.matrix[15]*m2.matrix[11]);
	result.matrix[15]= (m1.matrix[3]*m2.matrix[12])+(m1.matrix[7]*m2.matrix[13])+(m1.matrix[11]*m2.matrix[14])+(m1.matrix[15]*m2.matrix[15]);

	return result;
	}
