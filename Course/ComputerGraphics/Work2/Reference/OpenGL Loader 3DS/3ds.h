// 3ds.h: interface for the C3ds class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DS_H__04660DA5_F54E_4F1F_9BF8_2607D6D9D0B0__INCLUDED_)
#define AFX_3DS_H__04660DA5_F54E_4F1F_9BF8_2607D6D9D0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Texture.h"
#include <vector>
#include "vector.h"
#define  tVector3 CVector3
#include <list>
using namespace std;

class C3DS  
{
	// This is our 2D point class.  This will be used to store the UV coordinates.
	struct tVector2 {
		float x, y;
	};
	// This is our face structure.  This is is used for indexing into the vertex 
	// and texture coordinate arrays.  From this information we know which vertices
	// from our vertex array go to which face, along with the correct texture coordinates.
	struct tFace
	{
		unsigned short a,b,c;//vertIndex[3];			// indicies for the verts that make up this triangle
		short matIndex;		//The texture ID to use, which is the index into our texture array
	};
	
	// This holds the information for a material.  It may be a texture map of a color.
	// Some of these are not used, but I left them because you will want to eventually
	// read in the UV tile ratio and the UV tile offset for some models.
	struct tMaterialInfo
	{
		char  strName[255];			// The texture name
		char  strFile[255];			// The texture file name (If this is set it's a texture map)
		unsigned char  color[3];				// The color of the object (R, G, B)
		//CTexture cTxt;
		GLuint txtID;

	} ;
	// This holds all the information for our model/scene. 
	// You should eventually turn into a robust class that 
	// has loading/drawing/querying functions like:
	// LoadModel(...); DrawObject(...); DrawModel(...); DestroyModel(...);
	struct t3DObject 
	{
		int  numOfVerts;			// The number of verts in the model
		int  numOfFaces;			// The number of faces in the model
		int  numTexVertex;			// The number of texture coordinates
		char strName[255];			// The name of the object
		tVector3  *pVerts;			// The object's vertices
//		tVector3  *pNormals;		// The object's normals
		tVector2  *pTexVerts;		// The texture's UV coordinates
		tFace *pFaces;				// The faces information of the object
	//  物体的外包框  下面是我自己加上的,你可以不理会
		tVector3 tCenter; //中心点
		float xLen,yLen,zLen;//三个方向的长度的一半
	//  子物体列表
		list<t3DObject* >lstObj;
	};
	
	// This holds our model information.  This should also turn into a robust class.
	// We use STL's (Standard Template Library) vector class to ease our link list burdens. :)
	struct t3DModel 
	{
		vector<tMaterialInfo> vMaterials;	// The list of material information (Textures and colors)
		vector<t3DObject> vObject;			// The object list for our model
	};
CTexture m_txt;
public:
	bool Load3DS (char *p_filename);
	void Draw();

	bool Init(char *sFileName);

	t3DModel m_Model;
	C3DS();
	virtual ~C3DS();

};

#endif // !defined(AFX_3DS_H__04660DA5_F54E_4F1F_9BF8_2607D6D9D0B0__INCLUDED_)
