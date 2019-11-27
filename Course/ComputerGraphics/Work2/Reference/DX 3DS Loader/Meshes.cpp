
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 

#include "3DS.h"

struct VERTEX
{
    D3DXVECTOR3 pos;
    D3DXVECTOR3 normal;
    D3DXVECTOR2 uv;

    static const DWORD
        FVF=D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1;
};


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D           = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice     = NULL; // Our rendering device

LPD3DXMESH              g_pMesh          = NULL; // Our mesh object in sysmem
D3DMATERIAL9*           g_pMeshMaterials = NULL; // Materials for our mesh
LPDIRECT3DTEXTURE9*     g_pMeshTextures  = NULL; // Textures for our mesh
DWORD                   g_dwNumMaterials = 0L;   // Number of mesh materials
LPDIRECT3DVERTEXBUFFER9 
                        *g_pSubBuffer    =NULL;           //group for each sub
LPDIRECT3DINDEXBUFFER9  *g_pIndexBuffer  =NULL;
int*                     g_pNumVerts     =NULL;
int*                     g_pNumFaces     =NULL;

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Turn on ambient lighting 
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Load the mesh and build the material and texture arrays
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
    t3DModel temp={0};

    // Load the mesh from the specified file
    CLoad3DS loader;

    loader.Import3DS(&temp,"hua.3DS");

    g_dwNumMaterials=temp.numOfObjects;
    // We need to extract the material properties and texture names from the 
    // pD3DXMtrlBuffer
    g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
    g_pMeshTextures  = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
    g_pSubBuffer     = new LPDIRECT3DVERTEXBUFFER9[g_dwNumMaterials];
    g_pIndexBuffer   = new LPDIRECT3DINDEXBUFFER9[g_dwNumMaterials];
    g_pNumVerts      = new int[g_dwNumMaterials];  
    g_pNumFaces      = new int[g_dwNumMaterials];
    DWORD i;
    for(  i=0; i<g_dwNumMaterials; i++ )
    {
        int id=0;
        id=temp.pObject[i].materialID;
        // Copy the material
        D3DCOLORVALUE set={1,1,1,1};
        g_pMeshMaterials[i].Ambient=set;
        g_pMeshMaterials[i].Diffuse=set;
        g_pMeshMaterials[i].Specular=set;
        g_pMeshMaterials[i].Emissive.b=g_pMeshMaterials[i].Emissive.r=g_pMeshMaterials[i].Emissive.g=0;
        g_pMeshMaterials[i].Emissive.a=1;
        g_pMeshMaterials[i].Power=1;
       
        if(id>-1)
        {
            g_pMeshMaterials[i].Diffuse.r=temp.pMaterials[id].color[0]/255.0f;
            g_pMeshMaterials[i].Diffuse.g=temp.pMaterials[id].color[1]/255.0f;
            g_pMeshMaterials[i].Diffuse.b=temp.pMaterials[id].color[2]/255.0f;
            g_pMeshMaterials[i].Ambient=g_pMeshMaterials[i].Diffuse;
        }

        if(!temp.pObject[i].bHasTexture)
            g_pMeshTextures[i] = NULL;


        if(temp.pObject[i].bHasTexture && strlen(temp.pMaterials[id].strFile)>0)
        {
            // Create the texture
            // If texture is not in current folder, try parent folder
            if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, 
                                                    temp.pMaterials[id].strFile, 
                                                    &g_pMeshTextures[i] ) ) )
            {
                MessageBox(NULL, "Could not find texture map", "Meshes.exe", MB_OK);
            }
        }

        g_pNumVerts[i]=temp.pObject[i].numOfVerts;
        g_pNumFaces[i]=temp.pObject[i].numOfFaces;
        //fill sub buffer
        if( FAILED(g_pd3dDevice->CreateVertexBuffer(sizeof(VERTEX)*g_pNumVerts[i],D3DUSAGE_WRITEONLY,VERTEX::FVF,
                                    D3DPOOL_DEFAULT,&g_pSubBuffer[i],NULL)))
            return E_FAIL;
        //为了方便暂时使用 inde32 格式 可以自己来优化
        if( FAILED(g_pd3dDevice->CreateIndexBuffer(sizeof(DWORD)*g_pNumFaces[i]*3,
                                 D3DUSAGE_WRITEONLY,D3DFMT_INDEX32,D3DPOOL_DEFAULT,&g_pIndexBuffer[i],NULL)))
            return E_FAIL;
           
        VERTEX* pverts;
        int j;
        g_pSubBuffer[i]->Lock(0,0,(void**)&pverts,0);
        for(j=0;j<temp.pObject[i].numOfVerts;j++)
        {
            pverts[j].pos.x=temp.pObject[i].pVerts[j].x;
            pverts[j].pos.y=temp.pObject[i].pVerts[j].y;
            pverts[j].pos.z=-temp.pObject[i].pVerts[j].z;

            pverts[j].normal.x=temp.pObject[i].pNormals[j].x;
            pverts[j].normal.y=temp.pObject[i].pNormals[j].y;
            pverts[j].normal.z=-temp.pObject[i].pNormals[j].z;

            pverts[j].uv.x=temp.pObject[i].pTexVerts[j].x;
            pverts[j].uv.y=temp.pObject[i].pTexVerts[j].y;
        }
        g_pSubBuffer[i]->Unlock();

        DWORD *index;
        g_pIndexBuffer[i]->Lock(0,0,(void**)&index,0);
        for(j=0;j<temp.pObject[i].numOfFaces;j++)
        {
            index[j*3]=temp.pObject[i].pFaces[j].vertIndex[0];
            index[j*3+1]=temp.pObject[i].pFaces[j].vertIndex[1];
            index[j*3+2]=temp.pObject[i].pFaces[j].vertIndex[2];
        }
        g_pIndexBuffer[i]->Unlock();
    }

        

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( g_pMeshMaterials != NULL ) 
        delete[] g_pMeshMaterials;
    DWORD i;
    if( g_pMeshTextures )
    {
        for(i = 0; i < g_dwNumMaterials; i++ )
        {
            if( g_pMeshTextures[i] )
                g_pMeshTextures[i]->Release();
        }
        delete[] g_pMeshTextures;
    }
    
    if(g_pSubBuffer)
    {
        for(  i= 0; i < g_dwNumMaterials; i++ )
        {
            if(g_pSubBuffer[i])
                g_pSubBuffer[i]->Release();
        }
        delete[] g_pSubBuffer; 
    }

    if(g_pIndexBuffer)
    {
        for(  i= 0; i < g_dwNumMaterials; i++ )
        {
            if(g_pIndexBuffer[i])
                g_pIndexBuffer[i]->Release();
        }
        delete[] g_pIndexBuffer; 
    }

    if(g_pNumVerts)
        delete []g_pNumVerts;
    if(g_pNumFaces)
        delete []g_pNumFaces;

    if( g_pMesh != NULL )
        g_pMesh->Release();
    
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}



//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
    // Set up world matrix
    D3DXMATRIXA16 matWorld;
    D3DXMatrixRotationY( &matWorld, timeGetTime()/1000.0f );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the 
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-2.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    // Clear the backbuffer and the zbuffer
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
                         D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
    
    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Setup the world, view, and projection matrices
        SetupMatrices();

        // Meshes are divided into subsets, one for each material. Render them in
        // a loop
        for( DWORD i=0; i<g_dwNumMaterials; i++ )
        {
            // Set the material and texture for this subset
            g_pd3dDevice->SetMaterial( &g_pMeshMaterials[i] );
            g_pd3dDevice->SetTexture( 0, g_pMeshTextures[i] );
        
            // Draw the mesh subset
            g_pd3dDevice->SetStreamSource(0,g_pSubBuffer[i],0,sizeof(VERTEX));
            g_pd3dDevice->SetFVF(VERTEX::FVF);
            g_pd3dDevice->SetIndices(g_pIndexBuffer[i]);
            g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,g_pNumVerts[i],0,g_pNumFaces[i]);
        }

        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "D3D Tutorial", NULL };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( "D3D Tutorial", "D3D Tutorial 3ds Rendering", 
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    { 
        // Create the scene geometry
        if( SUCCEEDED( InitGeometry() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            // Enter the message loop
            MSG msg; 
            ZeroMemory( &msg, sizeof(msg) );
            while( msg.message!=WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                    Render();
            }
        }
    }

    UnregisterClass( "D3D Tutorial", wc.hInstance );
    return 0;
}



