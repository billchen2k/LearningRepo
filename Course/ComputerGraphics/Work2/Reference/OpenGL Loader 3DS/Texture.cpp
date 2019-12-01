
#include  "texture.h"
GLuint CTexture::LoadBMP(char *Filename)
{

	GLuint			texID;	
   	AUX_RGBImageRec *pImage = NULL;
	FILE *pFile = NULL;

	if(!Filename) 
		return false;

	// Open a file pointer to the BMP file and check if it was found and opened 
	if((pFile = fopen(Filename, "rb")) == NULL) 
	{
		// Display an error message saying the file was not found, then return NULL
		char buf[255];
		sprintf(buf,"Unable to load BMP File:%s",Filename);
		MessageBox(NULL, buf, "Error", MB_OK);
		ExitProcess(0);
		return false;
	}
	// Load the bitmap using the aux function stored in glaux.lib
	pImage = auxDIBImageLoad(Filename);				

	// Make sure valid image data was given to pImage, otherwise return false
	if(pImage == NULL)								
		return false;

	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &texID);

	// This sets the alignment requirements for the start of each pixel row in memory.
//	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Bind the texture to the texture arrays index and init the texture
	glBindTexture(GL_TEXTURE_2D, texID);
	
	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pImage->sizeX, 
					  pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);

	//Assign the mip map levels and texture info
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Now we need to free the image data that we loaded since openGL stored it as a texture

	if (pImage)										// If we loaded the image
	{
		if (pImage->data)							// If there is texture data
		{
			free(pImage->data);						// Free the texture data, we don't need it anymore
		//	delete []pImage->data;
		}
	//	delete pImage;
		free(pImage);								// Free the image structure
	}
	return texID;
}
/*
bool CTexture::LoadBMP(char *Filename)									// Load Bitmaps And Convert To Textures
{
	AUX_RGBImageRec *pImage = NULL;
	FILE *pFile = NULL;

	if(!Filename) 
		return false;

	// Open a file pointer to the BMP file and check if it was found and opened 
	if((pFile = fopen(Filename, "rb")) == NULL) 
	{
		// Display an error message saying the file was not found, then return NULL
		char buf[255];
		sprintf(buf,"Unable to load BMP File:%s",Filename);
		MessageBox(NULL, buf, "Error", MB_OK);
		ExitProcess(0);
		return false;
	}
	// Load the bitmap using the aux function stored in glaux.lib
	pImage = auxDIBImageLoad(Filename);				

	// Make sure valid image data was given to pImage, otherwise return false
	if(pImage == NULL)								
		return false;

	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &m_nTxt);

	// This sets the alignment requirements for the start of each pixel row in memory.
//	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Bind the texture to the texture arrays index and init the texture
	glBindTexture(GL_TEXTURE_2D, m_nTxt);
	
	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pImage->sizeX, 
					  pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);

	//Assign the mip map levels and texture info
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Now we need to free the image data that we loaded since openGL stored it as a texture

	if (pImage)										// If we loaded the image
	{
		if (pImage->data)							// If there is texture data
		{
			free(pImage->data);						// Free the texture data, we don't need it anymore
		//	delete []pImage->data;
		}
	//	delete pImage;
		free(pImage);								// Free the image structure
	}
	return true;
}
*/
bool CTexture::MakeTextureBind(char* TextureFileName,bool bLinear,bool bMip)
{
	bool status=true;			// Status Indicator
	AUX_RGBImageRec *Image=NULL;	

     ///////////////////load wall tex
	if (Image=auxDIBImageLoad(TextureFileName))
	{					
		glGenTextures(1, &m_nTxt);		// Create one Texture
   		glBindTexture(GL_TEXTURE_2D, m_nTxt);
        if(bLinear)
		{
			if(bMip)
			{
//                glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
//                glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
 	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	    	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, Image->sizeX, Image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, Image->data);
			}
			else
			{
                glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
                glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, Image->sizeX, Image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Image->data);				
			}
		}
		else
		{
			if(bMip)
			{
 	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	    	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, Image->sizeX, Image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, Image->data);
			}
			else
			{
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, Image->sizeX, Image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Image->data);				
			}
		}
	}
	else status=false;
	if (Image) {											// If Texture Exists
		if (Image->data) delete Image->data;				// If Texture Image Exists
		delete Image;
	}
	return status;				
}



bool CTexture::MakeSkinTextureBind(char* TextureFileName,
							   bool bLinear,bool bMip)
{
	bool state=true;			// Status Indicator
	unsigned char *Image=new unsigned char [256*256*3];	
	FILE* file;
    if((file= fopen(TextureFileName, "rb"))==NULL)
	{
	    state=false;
		return state;
	}
	char id[10],version;
	fread(id,     sizeof(char),10,  file);
	fread(&version,sizeof(char),1,  file);
	if ( strncmp( id, "Hunter3D00", 10 ) != 0 )
	{
		    fclose(file);
		    return false; // "Not a valid .skn file."
	}
	if ( version !=1 )
	{
	    fclose(file);
	    return false; // "Not a valid .skn file."
	}	

	fread(Image,sizeof(unsigned char),256*256*3,file);

    fclose(file);
    file=NULL;
				
	glGenTextures(1, &m_nTxt);		// Create one Texture
	glBindTexture(GL_TEXTURE_2D, m_nTxt);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    if(bLinear)
	{
		if(bMip)
			{
 	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	    	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, Image);
			}
			else
			{
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,256,256, 0, GL_RGB, GL_UNSIGNED_BYTE, Image);				
			}
	}
	else
	{
			if(bMip)
			{
 	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	    	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, Image);
			}
			else
			{
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 256,256, 0, GL_RGB, GL_UNSIGNED_BYTE, Image);				
			}
	}

    delete [] Image;				// If Texture Image Exists
	return state;				
}
/////////////////////////////////////////////////
bool CTexture::MakeAlphaTextureBind(char* TextureFileName)
{
	bool status=true;												// Status Indicator
	AUX_RGBImageRec *Image=NULL;									// Create Storage Space For The Texture
	unsigned char *alpha=NULL;

	////////////////////////////////////
	if (Image=auxDIBImageLoad(TextureFileName)) 
	{							
		alpha=new unsigned char[4*Image->sizeX*Image->sizeY];		// Create Memory For RGBA8-Texture
		for (int a=0; a<Image->sizeX*Image->sizeY; a++)
		{
			alpha[4*a]=Image->data[a*3];					// R
			alpha[4*a+1]=Image->data[a*3+1];				// G
			alpha[4*a+2]=Image->data[a*3+2];				// B
            ////////////Get max
            alpha[4*a+3]=(alpha[4*a+0]<alpha[4*a+1])?alpha[4*a+0]:alpha[4*a+1];
            if(alpha[4*a+2]<alpha[4*a+3])alpha[4*a+3]=alpha[4*a+2];


		}

		///////////////////////////////////////////////			
		glGenTextures(1, &m_nTxt);							// Create One Textures

		// Create Linear Filtered RGBA8-Texture
		glBindTexture(GL_TEXTURE_2D, m_nTxt);
   	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, Image->sizeX, Image->sizeY, GL_RGBA, GL_UNSIGNED_BYTE, alpha);
		delete [] alpha;
	}
	else status=false;
	if (Image) {											// If Texture Exists
		if (Image->data) delete Image->data;				// If Texture Image Exists
		delete Image;
		Image=NULL;
	}	
	///////////////////////////////////
    return status;
}
bool CTexture::MakeAlphaTextureBind(char* TextureFileName,char *AlphaFileName)
{
	bool status=true;												// Status Indicator
	AUX_RGBImageRec *Image=NULL;									// Create Storage Space For The Texture
	unsigned char *alpha=NULL;

	////////////////////////////////////
	if (Image=auxDIBImageLoad(TextureFileName)) 
	{							
		alpha=new unsigned char[4*Image->sizeX*Image->sizeY];		// Create Memory For RGBA8-Texture
		for (int a=0; a<Image->sizeX*Image->sizeY; a++)
		{
			alpha[4*a]=Image->data[a*3];					// R
			alpha[4*a+1]=Image->data[a*3+1];				// G
			alpha[4*a+2]=Image->data[a*3+2];				// B
		}
		/////////////////make alpha chanal
        if(AlphaFileName==NULL)return false;
	    FILE* file;
        if((file= fopen(AlphaFileName, "rb"))==NULL)
	      	return false;
		fseek(file,54,SEEK_SET);
		unsigned char temp[3];
		for ( a=0; a<Image->sizeX*Image->sizeY; a++)
		{
			fread(temp,sizeof(unsigned char),3,file);
            alpha[4*a+3]=(temp[0]>temp[1])?temp[0]:temp[1];
            if(temp[2]>alpha[4*a+3])alpha[4*a+3]=temp[2];
//          alpha[4*a+3]=(temp[0]+temp[1]+temp[2])/3;
			if(alpha[4*a+3]>50)alpha[4*a+3]=255;
		}
		fclose(file);
		///////////////////////////////////////////////			
		glGenTextures(1, &m_nTxt);							// Create One Textures
		// Create Linear Filtered RGBA8-Texture
		glBindTexture(GL_TEXTURE_2D, m_nTxt);
   	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, Image->sizeX, Image->sizeY, GL_RGBA, GL_UNSIGNED_BYTE, alpha);
		delete [] alpha;
	}
	else status=false;
	if (Image) {											// If Texture Exists
		if (Image->data) delete Image->data;				// If Texture Image Exists
		delete Image;
		Image=NULL;
	}	
	///////////////////////////////////
    return status;
}




bool  CTexture::MakeScreenTextureBind()
{
//	
	if(glIsTexture(m_nTxt)==GL_TRUE)
	{
//   		glBindTexture(GL_TEXTURE_2D, *TextureID);
//		glCopyTexSubImage2D(GL_TEXTURE_2D, 0,  0,0,   0,0,  512,512 );	
	}
	else
	{
		GLint Viewport[4];
        glGetIntegerv(GL_VIEWPORT, Viewport);
		int newWidth=128;

        unsigned char *pData=new unsigned char[newWidth*newWidth*3+6]; // +6 for safe
		/////////////找到pData(x,y)对应屏幕上的象素点(sx,sy)
		int sx,sy;  //标记新的位置
        unsigned char temp[6];
		for(int y=0;y<newWidth;y++)
			for(int x=0;x<newWidth;x++)
			{
			    sx=int(float(x*Viewport[2])/newWidth);
			    sy=int(float(y*Viewport[3])/newWidth);

	        	glReadPixels(sx,sy,1,1,
			                 GL_RGB,GL_UNSIGNED_BYTE,temp);

                pData[y*newWidth*3+x*3+0]=unsigned char(temp[0]*0.8f);
                pData[y*newWidth*3+x*3+1]=unsigned char(temp[1]*0.8f);
                pData[y*newWidth*3+x*3+2]=unsigned char(temp[2]*0.8f);
			}

        ////////////////////////////////////////////////////////////
		glGenTextures(1, &m_nTxt);		// Create one Texture
   		glBindTexture(GL_TEXTURE_2D, m_nTxt);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, newWidth,newWidth, 0, GL_RGB, GL_UNSIGNED_BYTE,pData);				

		delete [] pData;
	}
    return true;
}

typedef struct													// Create A Structure
{
	GLubyte	*imageData;											// Image Data (Up To 32 Bits)
	GLuint	bpp;												// Image Color Depth In Bits Per Pixel.
	GLuint	width;												// Image Width
	GLuint	height;												// Image Height
	GLuint	texID;												// Texture ID Used To Select A Texture
} TextureImage;	
bool CTexture::LoadTGA(char *filename)				// Loads A TGA File Into Memory
{    
	TextureImage Texture;
	TextureImage *texture = &Texture;
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};		// Uncompressed TGA Header
	GLubyte		TGAcompare[12];									// Used To Compare TGA Header
	GLubyte		header[6];										// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;									// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;										// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;											// Temporary Variable
	GLuint		type=GL_RGBA;									// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");							// Open The TGA File

	if(	file==NULL ||											// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)										// Did The File Even Exist? *Added Jim Strong*
			return FALSE;										// Return False
		else													// Otherwise
		{
			fclose(file);										// If Anything Failed, Close The File
			return FALSE;										// Return False
		}
	}

	texture->width  = header[1] * 256 + header[0];				// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];				// Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	texture->width	<=0	||									// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||									// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))						// Is The TGA 24 or 32 Bit?
	{
		fclose(file);											// If Anything Failed, Close The File
		return FALSE;											// Return False
	}

	texture->bpp	= header[4];								// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;							// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);			// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||								// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)							// Was Image Data Loaded
			free(texture->imageData);							// If So, Release The Image Data

		fclose(file);											// Close The File
		return FALSE;											// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)			// Loop Through The Image Data
	{															// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];								// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];		// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;						// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);												// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);						// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);				// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	
	if (texture[0].bpp==24)										// Was The TGA 24 Bits
	{
		type=GL_RGB;											// If So Set The 'type' To GL_RGB
	}
	m_nTxt = texture[0].texID;
	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
	free(texture[0].imageData);
	return true;												// Texture Building Went Ok, Return True
}
