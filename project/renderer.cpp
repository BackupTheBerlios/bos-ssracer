/*****************************************************************************
*
* File:  renderer.cpp
*
* BurnOut Studios - Super Street Racer
* Module:  Renderer
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 12, 2004
*
******************************************************************************
* Desc:  
*****************************************************************************/

#include "WmlVector3.h"
using namespace Wml;

// --- internal library includes --- //
#include "timer.h"
#include "renderer.h"
#include "renderervertexformats.h"
#include "gamestatemanager.h"
#include "settings.h"
#include "cinputconsole.h"
#include "macros.h"

// --- system includes --- //
#define STL_USING_ALL
#include "stl.h"



//-----------------------------------------------------------------------------
// static member declarations
//-----------------------------------------------------------------------------
CRenderer * CRenderer::ms_pkRenderer = NULL; 


//-----------------------------------------------------------------------------
// get functions for the singleton instance of the app
//-----------------------------------------------------------------------------
CRenderer & CRenderer::GetRenderer() {  return *ms_pkRenderer; } 
CRenderer * CRenderer::GetRendererPtr() {  return ms_pkRenderer;  } 


//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CRenderer::CRenderer (BOOL bFullScreen, HWND hWnd, UINT iWidth, UINT iHeight)
{
    m_hWnd = hWnd;
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_bFullScreen = bFullScreen;
    m_bConsoleDown = true; //$$$DEBUG
    GetWindowRect(hWnd, &m_rcWindow );
	ms_pkRenderer = this;
    m_bCursorVisible = false;
    
    //Create a structure to hold the settings for our device
    ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

    // set up some utility fonts
    m_kFontMap[FONT_DEFAULT]    = new CD3DFont( _T("Times"), 12, D3DFONT_BOLD );
    m_kFontMap[FONT_SYSTEM]     = new CD3DFont( _T("System"), 12, D3DFONT_BOLD|D3DFONT_ITALIC|D3DFONT_ZENABLE );
    m_kFontMap[FONT_SMALL]      = new CD3DFont( _T("Arial"), 8 );
    m_kFontMap[FONT_FRONT_END]  = new CD3DFont( _T("Arial"), 48 );

    // set up the skybox
    m_pSkyBox = new CD3DMesh(_T("skybox"));
    
    // set up the cameras
   	m_pkCameraMap[CAMERA_BUMPER]     = NULL;//new CD3DCamera();  // bumper camera
	m_pkCameraMap[CAMERA_CHASE]      = new CCameraChase();  // chase camera
	m_pkCameraMap[CAMERA_FREELOOK]   = new CCameraFreeLook(); // free look


	// set up default camera parameters for each main camera
    // 1 eye origin            2 look at pt      3 up vector
	// 1 field of view    2 aspect ratio  3 nearplane     4 farplane


	//--- bumper camera --- //
	//$$$TODO
	
	//--- chase camera --- //
	// eye 5 back, 3 up from objects position
	// look at car position
	// up is Y
	((CCameraChase *)m_pkCameraMap[CAMERA_CHASE])->SetViewParams( &D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 
                                                &D3DXVECTOR3( 0.0f, 0.0f, 1.0f) );
	// slightly wider FOV and shorter frustrum
	((CCameraChase *)m_pkCameraMap[CAMERA_CHASE])->SetProjParams( CAMERA_CHASE_DEFAULT_FOV, 1.0f ,1.0f ,8000.0f );


	//--- free look camera --- //	
	((CCameraFreeLook *)m_pkCameraMap[CAMERA_FREELOOK])->SetViewParams( &D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 
    			                                   &D3DXVECTOR3( 0.0f, 0.0f, 1.0f) );
	// wide FOV and a large frustrum
	((CCameraFreeLook *)m_pkCameraMap[CAMERA_FREELOOK])->SetProjParams( D3DX_PI/4.0f, 1.0f, 1.0f, 1000000.0f );


    // defaults to this camera
    //this->SetActiveCamera(CAMERA_FREELOOK);  //device isn't even set up yet so we can't use this funciton
    m_pActiveCamera = m_pkCameraMap[CAMERA_FREELOOK];
    m_eActiveCamType = CAMERA_FREELOOK;

    //$$$TEMP will be enabled by default once fully tested with map
    m_bVisCullingEnabled = false;

    // set debugging flags
    m_bDrawQNodeBBoxes = false;
    m_bDrawEntBBoxes = false;
    m_bDrawRects = false;
    m_bDrawWayPoints = false;

}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CRenderer::~CRenderer()
{

}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CRenderer::Initialize()
{
    HRESULT hr;
    
    //First of all, create the main D3D object. If it is created successfully we 
    //should get a pointer to an IDirect3D8 interface.
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if(m_pD3D == NULL)
    {
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_APP, IDS_RENDER_ERROR, "Could not initialize D3D!");
        #endif
        return E_FAIL;
    }

    D3DDISPLAYMODE d3ddm;
    if (m_bFullScreen == TRUE)
	{
        if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
        {
            return E_FAIL;
        }
	}
	else
	{
		d3ddm.Width = (UINT)m_iWidth;   // Set the screen width to the window width
		d3ddm.Height = (UINT)m_iHeight; // Set the screen height to the window height
		d3ddm.RefreshRate = 0;          // Set the refresh rate to default
		d3ddm.Format = D3DFMT_UNKNOWN; 
	}

    
    // fill in the settings for the d3d device
    m_d3dpp.Windowed = !m_bFullScreen;
    //m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    m_d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP; // flip back buffers
	m_d3dpp.BackBufferFormat = d3ddm.Format; // The color format
	m_d3dpp.BackBufferWidth  = d3ddm.Width;  // The back buffer width
	m_d3dpp.BackBufferHeight = d3ddm.Height; // The back buffer height
    m_d3dpp.BackBufferCount = 1;             //$$$DEBUG only double buffer for now
    m_d3dpp.hDeviceWindow = m_hWnd;
    m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    m_d3dpp.EnableAutoDepthStencil = TRUE;
    m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


    //Create a Direct3D device.
    if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_d3dpp.hDeviceWindow, 
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                   &m_d3dpp, &m_pd3dDevice)) )
    {
        return E_FAIL;
    }

    // show/hide the mouse cursor
    m_pd3dDevice->ShowCursor( FALSE );//$$$DEBUGm_bCursorVisible );
    
    // init the fonts for use
    std::map< unsigned int, CD3DFont * >::iterator it;
    for ( it=m_kFontMap.begin(); it!=m_kFontMap.end(); it++)  {
        hr = it->second->InitDeviceObjects( m_pd3dDevice );
        if( FAILED( hr ) )
           return DXTRACE_ERR( "m_kFontMap[it]->InitDeviceObjects", hr );
        it->second->RestoreDeviceObjects();
    }


    char szBuf[512];
    sprintf(szBuf, "%s%s", CSettingsManager::GetSettingsManager().GetGameSetting(DIRSTATICMESH).c_str(), "skybox");
    // use the current working directory trick to make DX load the textures from the same dir
    if (!SetCurrentDirectory(szBuf))
        return E_FAIL;
    sprintf(szBuf, "%s%s", szBuf, "\\skybox.x");
    // Load the skybox
    if( FAILED( m_pSkyBox->Create( m_pd3dDevice, _T(szBuf) ) ) )
        return E_FAIL;//D3DAPPERR_MEDIANOTFOUND;
    m_pSkyBox->RestoreDeviceObjects( m_pd3dDevice );
    // set the CWD back
    if (!SetCurrentDirectory(CSettingsManager::GetSettingsManager().GetGameSetting(DIRCURRENTWORKING).c_str()))
        return E_FAIL;

    // set up renderstates
    InitializeState();

    // set up static lighting
    if (!InitializeStaticLighting())
        return E_FAIL;

    // set up textures
    if (!InitializeTextures())
        return E_FAIL;

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: InitializeStaticLighting()
// Desc: Initialize static lighting for the scene
//-----------------------------------------------------------------------------
bool CRenderer::InitializeStaticLighting()
{
    HRESULT hr;

    D3DLIGHT9 d3dLight;

    // Initialize the structure.
    ZeroMemory(&d3dLight, sizeof(d3dLight));

    //$$$TEMP Set up a white point light for now
    // I'll fake the moonlight using the actual position of the moon on the skybox -J
    d3dLight.Type = D3DLIGHT_POINT;
    d3dLight.Diffuse.r  = 1.0f;
    d3dLight.Diffuse.g  = 1.0f;
    d3dLight.Diffuse.b  = 1.0f;
    d3dLight.Ambient.r  = 1.0f;
    d3dLight.Ambient.g  = 1.0f;
    d3dLight.Ambient.b  = 1.0f;
    d3dLight.Specular.r = 1.0f;
    d3dLight.Specular.g = 1.0f;
    d3dLight.Specular.b = 1.0f;

    d3dLight.Position.x = 0.0f;
    d3dLight.Position.y = 500.0f;
    d3dLight.Position.z = -10.0f;//-100.0f;

    d3dLight.Attenuation0 = 1.0f; 
    d3dLight.Range        = 50000.0f;//1000.0f;

    // Set the property information for the first light.
    hr = m_pd3dDevice->SetLight(0, &d3dLight);
    if (hr == D3DERR_INVALIDCALL )
        return false;// Handle failure
    
    hr = m_pd3dDevice->LightEnable(0, TRUE);
    if (hr == D3DERR_INVALIDCALL )
        return false;// Handle failure

    return true;
}



//-----------------------------------------------------------------------------
// Name: CreateMesh()
// Desc: creates a mesh object for an entity
//      pMesh = mesh object to create D3DX mesh object for 
//      pcFileName = full path to mesh and mesh filename with .x extension
//-----------------------------------------------------------------------------
int CRenderer::CreateMesh( CD3DMesh * pMesh, char * pcFileName )
{

    FILE* fp = fopen(pcFileName, "r");

    if (!fp)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "could not load mesh, path invalid %s", pcFileName);
        return 0;
    }

    HRESULT hr;
    if ( FAILED( hr = pMesh->Create( m_pd3dDevice, _T(pcFileName) )) )  {
	    #ifdef _DEBUG
	    CLog::GetLog().Write(LOG_APP, IDS_RENDER_ERROR, "could not load mesh");
	    #endif
        //DXTRACE_ERR_MSGBOX( _T("could not load single mesh"), hr );
        return 0;  // Failure
	}
    pMesh->UseMeshMaterials(true);
    pMesh->RestoreDeviceObjects( m_pd3dDevice );
 
    return 1;

}


//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
void CRenderer::DisplayBackBuffer ()
{
    // The first two parameters are a source rectangle and destination rectangle
    // The third parameter sets the destination window for this presentation
    // The fourth parameter is the DirtyRegion parameter and in most cases should be set to NULL

    CheckDevice(); //$$$DEBUG

    //$$$TODO Check for frame buffer effects and apply them here

    // flip buffers
    HRESULT hr;
    hr = m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
    if ( hr == D3DERR_DEVICELOST )  {
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_APP, IDS_RENDER_ERROR, "Rendering Failed");
        #endif
        DXTRACE_ERR_MSGBOX( "m_pd3dDevice->Present( NULL, NULL, NULL, NULL ))", hr );
    }


}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
bool CRenderer::CheckDevice()
{
    switch(m_pd3dDevice->TestCooperativeLevel())					//check device
    {
    case D3DERR_DEVICELOST: 
        return false;
    case D3DERR_DEVICENOTRESET:
        if(FAILED(m_pd3dDevice->Reset(&m_d3dpp)))				//reset device
        {
            MessageBox(m_hWnd,"Reset() failed!","CheckDevice()",MB_OK);
            return false;
        }
        Initialize(); //init scene again
        return true;
    default: 
        return true;
    }
}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
void CRenderer::ClearBackBuffer()  
{
    // clear the previous frame   
    //m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
    m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,20,100), 1.0f, 0 );
    //m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, NULL, 1.0f, 0 );//D3DCOLOR_XRGB(0,20,50)
    return;
}

bool CRenderer::BeginScene()  
{
    m_pd3dDevice->BeginScene();  // --- begin scene drawing commands
    return true;
}

void CRenderer::EndScene()  
{
    m_pd3dDevice->EndScene();  // --- end scene drawing commands     
}


int iDrawnEnt = 0, iTotalNodeEnt=0;
//-----------------------------------------------------------------------------
// Name:  RenderScene()
// Desc:  draw the scene using information from the game state
//-----------------------------------------------------------------------------
void CRenderer::RenderScene()
{
    // render the skybox first
    DrawSkyBox();

    // load the default render state
    m_pDefaultSB->Apply();

	#ifdef _DEBUG  // show developer info
    char tMsgA[25];
	sprintf( tMsgA, "%s %s","ssracer", BOSAPPVERSION);
	m_kFontMap[FONT_SYSTEM]->DrawText( 0, 0, D3DCOLOR_ARGB(100,255,255,255), tMsgA, D3DFONT_FILTERED|D3DFONT_BOTTOM);
	#endif


    // if culling enabled draw only renderable & static entities in the currently visible nodes
    if (m_bVisCullingEnabled && CGameStateManager::GetGameStateManager().GetScenePtr()->GetQuadTree()->IsInitialized())  {
        // clear drawn entities map so we dont overdraw
        m_kDrawnEntIDs.clear();

        // get visible quadtree nodes
        iDrawnEnt = iTotalNodeEnt = 0;  // init stat counters
        std::map <Vector3f, CQuadNode *> * pvVisible = CGameStateManager::GetGameStateManager().GetScenePtr()->GetQuadTree()->GetVisibleNodesPtr();
        for (std::map <Vector3f, CQuadNode *>::iterator it2 = pvVisible->begin();  it2 != pvVisible->end(); it2++)  {
            DrawQuadTreeNode(it2->second);// render this visible nodes contents
        }

        // draw dynamic entities that are visible in the frustum
        //$$$ TEMP just draw all vehicles for now
        std::vector <COpponentVehicle *>::iterator itVehicle;
        for (itVehicle = CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->begin(); itVehicle != CGameStateManager::GetGameStateManagerPtr()->GetOpponents()->end(); itVehicle++)  {
            DrawVehicle(*itVehicle);
        }
        // draw player vehicle
        if ( CGameStateManager::GetGameStateManagerPtr()->GetPlayerVehicle() )
            DrawVehicle(CGameStateManager::GetGameStateManagerPtr()->GetPlayerVehicle());
    }    
    else {  //just draw all entities if culling is disabled

        for (vector<CEntity *>::iterator it = CGameStateManager::GetGameStateManager().GetScenePtr()->m_vEntities.begin();
             it != CGameStateManager::GetGameStateManager().GetScenePtr()->m_vEntities.end();  it++)  
        {
            if ((*it)->getIsRenderable())
                DrawEntity(*it);
        } 
    }

    #ifdef _DEBUG
    //$$$NOTE normally we wouldn't draw ALL the planes but we don't have a BSP tree as of yet to cut this down...
    if (m_bDrawRects == true)  {
        for (vector<Rectangle3f *>::iterator it = CGameStateManager::GetGameStateManager().GetScenePtr()->m_vPlanes.begin();
        it != CGameStateManager::GetGameStateManager().GetScenePtr()->m_vPlanes.end();  it++)  
        {
            DrawRect(*it, 3.0f, D3DCOLOR_ARGB( 255, 55, 55, 255 ));
        }
    }
    //$$$DEBUG DRAW ALL WAYPOINTS
    if (m_bDrawWayPoints== true)  {
        // draw main set
        vector<CWaypoint *>::iterator it;
        for ( it = CGameStateManager::GetGameStateManager().GetScenePtr()->m_vWaypoints.begin();
        it != CGameStateManager::GetGameStateManager().GetScenePtr()->m_vWaypoints.end();  it++)  
        {
            if (it == CGameStateManager::GetGameStateManager().GetScenePtr()->m_vWaypoints.begin())
                DrawWayPoint(*it, 10.0f, D3DCOLOR_ARGB( 255, 255, 255, 255 ));  //first waypoint
            else if ( it == CGameStateManager::GetGameStateManager().GetScenePtr()->m_vWaypoints.end()-1)
                DrawWayPoint(*it, 10.0f, D3DCOLOR_ARGB( 255, 255, 55, 55 ));  //last waypoint
            else
                DrawWayPoint(*it, 7.0f, D3DCOLOR_ARGB( 255, 55, 155, 155 ));
        }
        // draw all shortcut sets
        if (!CGameStateManager::GetGameStateManager().GetScenePtr()->m_vWPShortCut1.empty())  {
            for ( it = CGameStateManager::GetGameStateManager().GetScenePtr()->m_vWPShortCut1.begin();
            it != CGameStateManager::GetGameStateManager().GetScenePtr()->m_vWPShortCut1.end();  it++)  
            {
                if (!*it)
                DrawWayPoint(*it, 7.0f, D3DCOLOR_ARGB( 255, 55, 255, 155 ));
            }
        }
        
        if (!CGameStateManager::GetGameStateManager().GetScenePtr()->m_vWPShortCut2.empty())  {
            for ( it = CGameStateManager::GetGameStateManager().GetScenePtr()->GetShortCut2()->begin();
            it != CGameStateManager::GetGameStateManager().GetScenePtr()->GetShortCut2()->end();  it++)  
            {
                DrawWayPoint(*it, 7.0f, D3DCOLOR_ARGB( 255, 55, 255, 155 ));
            }
        }
        if (!CGameStateManager::GetGameStateManager().GetScenePtr()->m_vWPShortCut3.empty())  {
            for ( it = CGameStateManager::GetGameStateManager().GetScenePtr()->GetShortCut3()->begin();
            it != CGameStateManager::GetGameStateManager().GetScenePtr()->GetShortCut3()->end();  it++)  
            {
                DrawWayPoint(*it, 7.0f, D3DCOLOR_ARGB( 255, 55, 255, 155 ));
            }
        }



    }
    #endif
}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
void CRenderer::Cleanup()
{
    // destroy the fonts for use
    HRESULT hr;
    std::map< unsigned int, CD3DFont * >::iterator it;
    for ( it=m_kFontMap.begin(); it!=m_kFontMap.end(); it++)  {
        hr = it->second->DeleteDeviceObjects();
        if( FAILED( hr ) )
           DXTRACE_ERR_MSGBOX( "m_kFontMap::it->DeleteDeviceObjects", hr );
    }

    // destroy the skybox
    m_pSkyBox->InvalidateDeviceObjects();
    m_pSkyBox->Destroy();
    SAFE_DELETE( m_pSkyBox );

    // release state block
    std::map<StateBlockType, LPDIRECT3DSTATEBLOCK9>::iterator it2;
    for ( it2=m_pSBMap.begin(); it2!=m_pSBMap.end(); it2++)  {
        SAFE_RELEASE(it2->second);
    }
    SAFE_RELEASE(m_pSavedSB);  // not in the SB map

    // release HUD and frontend textures
    std::map<std::string, LPDIRECT3DTEXTURE9>::iterator it3;
    for ( it3=m_pTextureMap.begin(); it3!=m_pTextureMap.end(); it3++)  {
        SAFE_RELEASE(it3->second);
    }


    // shutdown d3d interfaces
    if( m_pd3dDevice != NULL)
        m_pd3dDevice->Release();
    if( m_pD3D != NULL)
        m_pD3D->Release();
   
}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
void CRenderer::ToggleFullScreen( int  riNewWidth, int riNewHeight )
{
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_RENDER_MSG, "Toggling Fullscreen to..." );
    CLog::GetLog().Write( LOG_APP, "\tx resolution: %d y resolution %d",
                          riNewWidth, riNewHeight );
    #endif

    m_d3dpp.BackBufferWidth = (UINT)riNewWidth;  //$$$DEBUG
    m_d3dpp.BackBufferHeight = (UINT)riNewHeight;
    m_d3dpp.Windowed = !m_d3dpp.Windowed;

    if ( m_d3dpp.Windowed )
    {
        m_d3dpp.FullScreen_RefreshRateInHz = 0;
    }
    else
    {
        GetWindowRect(m_d3dpp.hDeviceWindow,&m_rcWindow);
        m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    }

    OnDeviceLost();
    ResetDevice();  

    if ( m_d3dpp.Windowed )
    {
        SetWindowPos(m_d3dpp.hDeviceWindow, 
            NULL, 
            m_rcWindow.left,
            m_rcWindow.top, 
            m_rcWindow.right - m_rcWindow.left,
            m_rcWindow.bottom - m_rcWindow.top,
            SWP_NOZORDER | SWP_DRAWFRAME | SWP_SHOWWINDOW);
    }

    //riNewWidth = m_rcWindow.right - m_rcWindow.left + 1;
    //riNewHeight = m_rcWindow.bottom - m_rcWindow.top + 1;
}


void CRenderer::ResetDevice ()
{
    m_hResult = m_pd3dDevice->Reset(&m_d3dpp);
    
    //m_pqDefaultFont->OnResetDevice();
    InitializeState();
    //m_spkCamera->Update();`
}


void CRenderer::OnDeviceLost ()
{
    //m_pqDefaultFont->OnLostDevice();
}



//-----------------------------------------------------------------------------
// Name:  IntitializeState()
// Desc:  sets up the default rendering state and commonly used state blocks
//-----------------------------------------------------------------------------
void CRenderer::InitializeState ()
{
    //--- set up the default state block ---//
    m_pd3dDevice->BeginStateBlock();

    // z-buffering
    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);

    m_pd3dDevice->SetRenderState( D3DRS_CLIPPING, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
    
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00202020 );

    // Set up the texture 
    m_pd3dDevice->SetTexture(0, NULL);
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP ); 
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP ); 

    // disable texture transparencies
    m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);

    // save this as the default state block
    m_pd3dDevice->EndStateBlock( &m_pSBMap[RENSB_DEFAULT] );
    m_pDefaultSB = m_pSBMap[RENSB_DEFAULT];

    
    //--- set up other utility state blocks ---//

    // set up the debug info state block //
    m_pd3dDevice->BeginStateBlock();
    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
    m_pd3dDevice->SetRenderState( D3DRS_CLIPPING, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00202020 );

    // Set up the texture 
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP ); 
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP ); 
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
    m_pd3dDevice->SetFVF( D3DFVF_D3DVertex );
    m_pd3dDevice->EndStateBlock( &m_pSBMap[RENSB_DEBUGSTATE] );


    // set up the HUD state block //
    m_pd3dDevice->BeginStateBlock();
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );  //no lighting
    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);      // Enable depth testing.
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP ); 
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP ); 
    // for transparencies
    m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
    m_pd3dDevice->SetFVF( D3DFVF_D3DTMVertex );
    m_pd3dDevice->EndStateBlock( &m_pSBMap[RENSB_HUD] );

    // initialize the saved state block for use
    m_pd3dDevice->CreateStateBlock( D3DSBT_ALL, &m_pSavedSB);

    // restore the default renderstate
    m_pDefaultSB->Apply();

    return;
}


//-----------------------------------------------------------------------------
// Name:  InitializeTextures()
// Desc:  sets up the default rendering state and commonly used state blocks
//-----------------------------------------------------------------------------
bool CRenderer::InitializeTextures ()
{
    // set working dir to the texture dir
    if (!SetCurrentDirectory(CSettingsManager::GetSettingsManager().GetGameSetting(DIRTEXTURES).c_str()))
        return false;

    // load HUD texture filenames into the texture map
    m_pTextureMap["rpm_gauge.bmp"] = NULL;
    m_pTextureMap["needle.bmp"] = NULL;
    m_pTextureMap["mpg_gear.bmp"] = NULL;

    // load front end texture filenames into the texture map
    m_pTextureMap["fe_main_menu.bmp"] = NULL;
    m_pTextureMap["fe_quit.bmp"] = NULL;    


    // load textures //
    for(std::map< std::string, LPDIRECT3DTEXTURE9 >::iterator it = m_pTextureMap.begin();
    it != m_pTextureMap.end(); it++)  {
        if(D3DXCreateTextureFromFileEx(m_pd3dDevice, 
            (LPCSTR)it->first.data(), 
            D3DX_DEFAULT, 
            D3DX_DEFAULT,
            1,
            0,
            D3DFMT_UNKNOWN,
            D3DPOOL_DEFAULT,
            D3DX_FILTER_NONE,
            D3DX_FILTER_NONE, 
            D3DCOLOR_ARGB(255,255,0,255), //alpha color
            NULL,
            NULL,
            &it->second) != D3D_OK) {
            CLog::GetLog().Write(LOG_MISC, "ERROR Renderer: could not load texture %s%s", (char *)CSettingsManager::GetSettingsManager().GetGameSetting(DIRTEXTURES).data(),(char*)it->first.data());
        }
/*        if(D3DXCreateTextureFromFile(m_pd3dDevice, (LPCSTR)it->first.data(), &it->second) != D3D_OK) {
            CLog::GetLog().Write(LOG_MISC, "ERROR Renderer: could not load texture %s%s", (char *)CSettingsManager::GetSettingsManager().GetGameSetting(DIRTEXTURES).data(),(char*)it->first.data());
        }
        */
    }

    // set the CWD back
    if (!SetCurrentDirectory(CSettingsManager::GetSettingsManager().GetGameSetting(DIRCURRENTWORKING).c_str()))
        return false;



    return true;
}



//-----------------------------------------------------------------------------
// Name:  SetCamera()
// Desc:  set the view and projection matrices in the new camera model
// Defaults: eCameraName = CAMERA_FREELOOK
//-----------------------------------------------------------------------------
CD3DCamera * CRenderer::SetCamera( CD3DCamera* pkCamera, CameraType eCameraName)
{ 
    assert(pkCamera);
    m_pkCameraMap[eCameraName] = pkCamera; 
    
    // set the view and projection matrices for the device
    m_pd3dDevice->SetTransform( D3DTS_VIEW, pkCamera->GetViewMatrix() );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, pkCamera->GetProjMatrix() );    

    // re-compute the frustrum of the new camera


    return m_pkCameraMap[eCameraName]; 
}



//-----------------------------------------------------------------------------
// Name:  GetCamera()
// Desc:  get a pointer to a camera specified by name
// Defaults: eCameraName = CAMERA_FREELOOK
//-----------------------------------------------------------------------------
CD3DCamera * CRenderer::GetCameraPtr (CameraType eCameraName)
{
    return m_pkCameraMap[eCameraName]; 
}



//-----------------------------------------------------------------------------
// Name:  Click()
// Desc:  updates any active camera positions
//-----------------------------------------------------------------------------
void CRenderer::Click()
{
    #ifdef _DEBUG
    assert(m_pActiveCamera);
    #endif    

    // get next frame from camera
    m_pActiveCamera->FrameMove(CTimer::GetTimer().GetTimeElapsed());

    // set the new view matrix for the camera in the D3Ddevice
    m_pd3dDevice->SetTransform( D3DTS_VIEW, m_pActiveCamera->GetViewMatrix() );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, m_pActiveCamera->GetProjMatrix() );   

}






//-----------------------------------------------------------------------------
// Name:  SetActiveCamera()
// Desc:  sets the active camera to the one specified by name
// name must be one of the enumerated types or this will fail
//-----------------------------------------------------------------------------
bool CRenderer::SetActiveCamera( CameraType eCameraName )  { 
    // check if there even exists a camera to set
    if (!m_pkCameraMap[eCameraName])
        return 0;

    // if it's a bumper cam or chase cam there has to be a vehicle to track
    if (eCameraName == CAMERA_CHASE || eCameraName == CAMERA_BUMPER)  {
        if (!CGameStateManager::GetGameStateManager().GetPlayerVehicle())  {
            CLog::GetLog().Write(LOG_GAMECONSOLE, "Renderer:  WARNING you need to set the camera to track a vehicle!");
        }
    }
    m_pActiveCamera = m_pkCameraMap[eCameraName];
    m_eActiveCamType = eCameraName; 

    // set the new view matrix for the active camera in the D3Ddevice
    m_pd3dDevice->SetTransform( D3DTS_VIEW, m_pActiveCamera->GetViewMatrix() );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, m_pActiveCamera->GetProjMatrix() );   

    return 1;
};





//END renderer.cpp ============================================================